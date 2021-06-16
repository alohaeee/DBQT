#ifndef BDCOURSE_EDITPROPERTYDIALOG_H
#define BDCOURSE_EDITPROPERTYDIALOG_H

#include <QDialog>
#include "Properties.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
	class EditPropertyDialog;
}
QT_END_NAMESPACE

class EditPropertyDialog : public QDialog
{
Q_OBJECT

public:
	EditPropertyDialog(QSqlTableModel* model, int index, QWidget* parent = nullptr);
	~EditPropertyDialog() override;

private:
	int index = 0;
	Ui::EditPropertyDialog* ui;
	Properties properties;
};


#endif //BDCOURSE_EDITPROPERTYDIALOG_H
