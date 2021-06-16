#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "EditPropertyDialog.h"
#include "CreatePropertyDialog.h"
#include "Utils.h"

auto pricol(int n, QSqlTableModel* table, int row) -> void
{
	QMessageBox msgBox; //Стоит спросить пользователя уверен ли он
	QString str = QString("Уверены что хотите удалить запись о виде \"%1\"?").arg(
			table->index(row, 1).data().toString());
	for (int i = 0; i < n; i++)
	{
		str += "ТОЧНА?";
	}
	msgBox.setText(str);
	msgBox.setWindowTitle("Подтверждение");
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setInformativeText("Данные будут удалены безвозвратно!");
	QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
	QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
	msgBox.setDefaultButton(pButtonNo);
	msgBox.exec();
	if (msgBox.clickedButton() == pButtonYes)
	{
		pricol(n + 1,table,row);
	}
	else
	{
		table->removeRow(row);
		table->submitAll();
	}
}

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent)
		  , ui(new Ui::MainWindow)
{
	instance = this;
	ui->setupUi(this);
	if (!CreateConnection())     //Установка соединения с БД, оно будет существовать до завершения программы
	{
		exit(-1);       //Аварийное завершение работы при ошибке
	}

	ui->tabWidget->clear();

//	CreateTableView(CreateTabForTable("Договор с клиентом"), CreateTable("Договор с клиентом"));
//	CreateAllForTable("Директор");

	for (const auto& tableName : GetDBTablesHeaders())
	{
		SetForeignKeyMeta(tableName);
		CreateAllForTable(tableName);
	}



	connect(ui->createElement, &QPushButton::clicked, [this]() {
		CreatePropertyDialog dialog(GetCurrentSelectedTable());
		dialog.setModal(true);
		dialog.exec();
	});

	connect(ui->editElement, &QPushButton::clicked, [this]() {
		auto table = GetCurrentSelectedTable();
		if (table->rowCount())
		{
			int row = GetCurrentSelectedTableView()->currentIndex().row();
			EditPropertyDialog dialog(table, (row > 0 ? row : 0));
			dialog.setModal(true);
			dialog.exec();
		}
	});

	connect(ui->deleteElement, &QPushButton::clicked, [this]() {


		auto row = GetCurrentSelectedTableView()->currentIndex().row();
		auto table = GetCurrentSelectedTable();
		if (table)
		{
			auto val = RowToString(table, row);

			QMessageBox msgBox; //Стоит спросить пользователя уверен ли он
			msgBox.setMinimumSize(700, 700);
			QString str = QString("Уверены что хотите удалить запись %1 \"%2\"?").arg(
					table->tableName(),
					val);
			msgBox.setText(str);
			msgBox.setWindowTitle("Подтверждение");
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setInformativeText("Данные будут удалены безвозвратно!");
			QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
			QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
			msgBox.setDefaultButton(pButtonNo);
			msgBox.exec();
			if (msgBox.clickedButton() == pButtonYes)
			{
				table->removeRow(row);
				table->submitAll();
			}
		}
	});


}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::CreateConnection()
{
	auto db = QSqlDatabase::addDatabase("QPSQL");   //Драйвер PostreSQL
	db.setHostName("localhost");                            //Адрес сервера
	db.setDatabaseName("director_audio");                              //Имя БД
	db.setUserName("postgres");                             //Имя пользователя
	db.setPassword("123");                  //Пароль пользователя и нет,                    //это не мой обычный пароль
	db.setPort(5432);                                    //Номер порта
	if (!db.open())
	{                                       //Создание связи
		QMessageBox msgBox;
		QString str = QString("Ошибка при открытии базы данных:");
		msgBox.setText(str);
		msgBox.setWindowTitle("Ошибка");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setInformativeText(db.lastError().text());
		msgBox.exec();                                      //При ошибке отображение сообщения
		return false;
	}
	return true;
}

QSqlTableModel* MainWindow::CreateTable(const QString& tableName)
{
	QSqlTableModel* model = nullptr;
	QSqlRelationalTableModel* relationModel = nullptr;
	const auto& meta = TableMetaInfoHolder::Instance().GetTableMetaInfo(tableName);
	if (!meta.IsEmpty()) // Если мета не пустая
	{
		relationModel = new QSqlRelationalTableModel(this, QSqlDatabase::database());
		model = relationModel;
	}
	else
	{
		model = new QSqlTableModel(this, QSqlDatabase::database()); //Подключение модели к БД
	}

	model->setTable(tableName);                                //Выбор таблицы


	if (relationModel)
	{
		for(auto&& [key, value]: meta.GetForeignKeyRelation())
		{
			relationModel->setRelation(relationModel->fieldIndex(key), value);
		}
	}
	model->select();                                          //Загрузка данных из таблицы в модель
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
	model->sort(model->fieldIndex(PrimaryKeyName(model)),
	            Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
	models[tableName] = model;

	for (int i = 0; i < model->columnCount(); i++)
	{
		auto replacedStr = ReplaceUnderscoreWithSpace(model->headerData(i, Qt::Orientation::Horizontal).toString());
		model->setHeaderData(i, Qt::Orientation::Horizontal, replacedStr);
	}

	ShowMessageBoxError("Ошибка при создании модели", model);
	return model;
}

QWidget* MainWindow::CreateTabForTable(const QString& tableName)
{
	auto widget = new QWidget();

	ui->tabWidget->addTab(widget, ReplaceUnderscoreWithSpace(tableName));

	widget->setLayout(new QGridLayout());


	return widget;
}

QTableView* MainWindow::CreateTableView(QWidget* widget, QAbstractTableModel* model)
{
	auto view = new QTableView();

	widget->layout()->addWidget(view);
	view->setParent(widget);
	view->setModel(model);                           //Подключение таблицы к представлению
	view->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	views.push_back(view);

	return view;
}

void MainWindow::CreateAllForTable(const QString& tableName)
{
	CreateTableView(CreateTabForTable(tableName), CreateTable(tableName));
}

QSqlTableModel* MainWindow::GetTable(const QString& tableName) const
{
	if (auto model = models.find(tableName); model != models.end())
	{
		return model.value();
	}
	return nullptr;
}

QSqlTableModel* MainWindow::GetCurrentSelectedTable() const
{
	auto index = GetCurrentSelectedTableIndex();
	return GetTable(ReplaceSpaceWithUnderscore(ui->tabWidget->tabText(index)));
}

int MainWindow::GetCurrentSelectedTableIndex() const
{
	return ui->tabWidget->currentIndex();
}

QTableView* MainWindow::GetCurrentSelectedTableView() const
{
	auto index = GetCurrentSelectedTableIndex();
	return views[index];
}



