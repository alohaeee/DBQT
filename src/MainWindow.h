#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	static MainWindow& Instance()
	{
		return *instance;
	}
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	bool CreateConnection();        //Создание соединения с БД

	QWidget* CreateTabForTable(const QString& tableName);
	QSqlTableModel* CreateTable(const QString& tableName);
	QTableView* CreateTableView(QWidget* widget, QAbstractTableModel* model);

	void CreateAllForTable(const QString& tableName);

	QSqlTableModel* GetTable(const QString& tableName) const;
	QSqlTableModel* GetCurrentSelectedTable() const;
	int GetCurrentSelectedTableIndex() const;
	QTableView* GetCurrentSelectedTableView() const;

private:
	Ui::MainWindow *ui;

	QMap<QString, QSqlTableModel*> models;
	QVector<QTableView*> views;

	static inline MainWindow* instance = nullptr;
};


#endif // MAINWINDOW_H
