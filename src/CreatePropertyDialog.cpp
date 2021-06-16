//
//

// You may need to build the project (run Qt uic code generator) to get "ui_createpropertydialog.h" resolved

#include "CreatePropertyDialog.h"
#include "ui_createpropertydialog.h"

CreatePropertyDialog::CreatePropertyDialog(QSqlTableModel* model, QWidget* parent) :
		QDialog(parent), ui(new Ui::CreatePropertyDialog), properties(model)
{
	ui->setupUi(this);
	properties.CreateProperties(ui->content);

	connect(ui->exitButton, &QPushButton::clicked, [this]() {
		close();
	});

	connect(ui->cancelButton, &QPushButton::clicked, [this]() {
		properties.ForEachProperty([](auto& property) {
			property->Clear();
		});
	});

	connect(ui->createButton, &QPushButton::clicked, [this]() {
		properties.GetModel()->insertRows(properties.GetModel()->rowCount(), 1);
		properties.SetPropertiesValueToRecord(properties.ModelSize() - 1);
		if (ShowMessageBoxError("Ошибка при создании", properties.GetModel()))
		{
			properties.GetModel()->removeRow(properties.GetModel()->rowCount() - 1);
		}
		else
		{
			close();
		}
	});
//	ui->createButton->setEnabled(false);
//	properties.ForEachProperty([button = ui->createButton, this](auto& property) {
//		if (std::static_pointer_cast<BooleanProperty>(property))
//		{
//			return;
//		}
//		property->SetOnEditHandler([button, this](auto& property) {
//			bool enabled = true;
//			for (auto& prop: properties.GetProperties())
//			{
//				if (std::static_pointer_cast<BooleanProperty>(prop))
//				{
//					continue;
//				}
//				enabled &= !prop->IsEmpty();
//			}
//			button->setEnabled(enabled);
//		});
//	});
}

CreatePropertyDialog::~CreatePropertyDialog()
{
	delete ui;
}

