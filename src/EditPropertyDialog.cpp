#include "EditPropertyDialog.h"
#include "ui_EditPropertyDialog.h"
#include "MainWindow.h"
#include "PropertyInspectorFactory.h"


EditPropertyDialog::EditPropertyDialog(QSqlTableModel* model, int cIndex, QWidget* parent) :
		QDialog(parent), ui(new Ui::EditPropertyDialog), properties(model), index{cIndex}
{
	setMinimumSize(600,600);
	ui->setupUi(this);
	ui->saveButton->setEnabled(false);

	properties.CreatePropertiesForRecord(ui->contentWidget, index);

	connect(ui->nextButton, &QPushButton::clicked, [this](){
		if (index + 1 < properties.ModelSize())
		{
			ui->saveButton->setEnabled(false);
			index++;
			properties.FillPropertiesFromRecord(index);
		}
	});
	connect(ui->prevButton, &QPushButton::clicked, [this](){
		if (index - 1 >= 0)
		{
			ui->saveButton->setEnabled(false);
			index--;
			properties.FillPropertiesFromRecord(index);
		}
	});

	connect(ui->cancelButton, &QPushButton::clicked, [this]() {
		properties.FillPropertiesFromRecord(index);
	});

	connect(ui->saveButton, &QPushButton::clicked, [this]() {
		QMessageBox msgBox; //Стоит спросить пользователя уверен ли он
		msgBox.setMinimumSize(700, 700);
		QString str = QString("Уверены что хотите сохранить запись запись?");
		msgBox.setText(str);
		msgBox.setWindowTitle("Подтверждение");
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setInformativeText("Данные будут измененны безвозратно!");
		QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
		QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
		msgBox.setDefaultButton(pButtonNo);
		msgBox.exec();
		if (msgBox.clickedButton() == pButtonYes)
		{
			properties.SetPropertiesValueToRecord(index);
		}

	});

	connect(ui->exitButton, &QPushButton::clicked, [this]() {
		close();
	});

	properties.ForEachProperty([button = ui->saveButton, this](auto& property) {
		property->SetOnEditHandler([button](auto& property) {
			button->setEnabled(true);
		});
	});


}

EditPropertyDialog::~EditPropertyDialog()
{
	delete ui;
}
