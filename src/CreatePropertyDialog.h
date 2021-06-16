//
//

#ifndef BDCOURSE_CREATEPROPERTYDIALOG_H
#define BDCOURSE_CREATEPROPERTYDIALOG_H

#include <QDialog>
#include "Properties.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class CreatePropertyDialog;
}
QT_END_NAMESPACE

class CreatePropertyDialog : public QDialog
{
Q_OBJECT

public:
	CreatePropertyDialog(QSqlTableModel* model, QWidget* parent = nullptr);
	~CreatePropertyDialog() override;

private:
	Ui::CreatePropertyDialog* ui;
	Properties properties;
};


#endif //BDCOURSE_CREATEPROPERTYDIALOG_H
