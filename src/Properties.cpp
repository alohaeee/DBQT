#include "Properties.h"
#include "Utils.h"
#include "MainWindow.h"

Properties::Properties(QSqlTableModel* model) : model{model}
{

}

void Properties::CreateProperties(QWidget* parent)
{
	CreateProperties(parent, model->record());
}

void Properties::CreatePropertiesForRecord(QWidget* parent, int recordIndex)
{
	CreateProperties(parent, model->record(recordIndex));
}

void Properties::FillPropertiesFromRecord(int recordIndex)
{
	if (model)
	{
		if (properties.empty())
		{
			assert(!"Properties not created");
			return;
		}
		auto record = model->record(recordIndex);
		for (int i = 0; i < record.count(); i++)
		{
			if (auto property = GetPropertyWithName(record.fieldName(i)))
			{
				property->SetValue(record.value(i));
			}
		}
	}
	else
	{
		assert(!"Null model");
	}
}

void Properties::ForEachProperty(const Properties::ForEachHandler& handler)
{
	std::for_each(properties.begin(), properties.end(), handler);
}

void Properties::SetPropertiesValueToRecord(int recordIndex)
{
	if (model)
	{
		auto record = model->record();
		ForEachProperty([=](const auto& property) {
			int index = record.indexOf(property->GetName());
			//qDebug() << property->GetName() << "ИНДЕКС: " << index << property->GetValue();
			if(!model->setData(model->index(recordIndex, index), property->GetValue()))
			{
				qDebug() << "Ошибка при добавлении";
				ShowMessageBoxError("ошибка", model);
			};
		});

		model->submitAll();
	}
	else
	{
		assert(!"Null model");
	}
}

IProperty::Ptr Properties::GetPropertyWithName(const QString& name)
{
	auto iter = std::find_if(properties.begin(), properties.end(), [name](const auto& property) {
		return property->GetName() == name;
	});
	if (iter != properties.end())
	{
		return *iter;
	}
	return nullptr;
}

void Properties::CreateProperties(QWidget* parent, const QSqlRecord& record)
{
	if (model)
	{
		auto primaryKeyName = PrimaryKeyName(model);
		const auto& meta = TableMetaInfoHolder::Instance().GetTableMetaInfo(model->tableName());
		for (int i = 0; i < record.count(); i++)
		{
			auto recordField = record.field(i);
//			qDebug() << model->tableName() << recordField.name() << recordField.length();
//			for (auto&& [key,value]: meta.GetForeignKeyRelation())
//			{
//
//				qDebug() << recordField.name() << key << value.tableName() << value.indexColumn() << value.displayColumn() << (key == recordField.name());
//			}
			auto relation = meta.GetKeyRelation(recordField.name());
			relation = (relation ? relation : meta.GetKeyRelationByDisplay(recordField.name()));
			if (relation)
			{
				auto table = MainWindow::Instance().GetTable(relation->tableName());
				QStringList vars;
				QList<int> index;
				//qDebug() << table->rowCount();
				for (int j = 0; j < table->rowCount(); j++)
				{
					auto foreignRecord = table->record(j);
					vars.push_back(foreignRecord.field(relation->displayColumn()).value().toString());
					index.push_back(foreignRecord.field(relation->indexColumn()).value().toInt());
				}
				properties.push_back(ForeignKeyProperty::Create(parent, recordField, vars, index));
			}
			// Primary key не даём редактироват
			else if (recordField.name() != primaryKeyName)
			{
				properties.push_back(PropertyInspectorFactory::CreateProperty(parent, recordField));
			}


		}
	}
	else
	{
		assert(!"Null model");
	}
}
