#include "Utils.h"
#include "PropertyInspectorFactory.h"

QVector<QString> GetDBTablesHeaders()
{
	QVector<QString> result;
	QSqlQuery query;
	if (query.exec("SELECT * FROM INFORMATION_SCHEMA.TABLES"))
	{
		while (query.next())
		{
			if (query.value("table_schema") == "public")
			{
				result.push_back(query.value("table_name").toString());
			}
		}
	}
	return result;
}

QString RowToString(QSqlTableModel* model, int index)
{
	QString result = "";
	for (int i = 0; i < model->columnCount(); i++)
	{
		result += model->index(index, i).data().toString() + "; ";
	}
	return result;
}

QString PrimaryKeyName(QSqlTableModel* model)
{
	if (model)
	{
		auto primaryKey = model->primaryKey();
		if (primaryKey.count())
		{
			return primaryKey.field(0).name();
		}
	}
	return {};
}

bool ShowMessageBoxError(const QString& text, QSqlQueryModel* model)
{
	QSqlError lastError;
	if (model)
	{
		lastError = model->lastError();
	}
	else
	{
		lastError = QSqlDatabase::database().lastError();
	}

	if (lastError.isValid())
	{
		QString title = "Ошибка SQL";
		QMessageBox msgBox;
		if (auto table = qobject_cast<QSqlTableModel*>(model))
		{
			title += QString(" [IN MODEL: %1]").arg(table->tableName());
		}
		msgBox.setText(text);
		msgBox.setWindowTitle(title);
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setInformativeText(lastError.text());
		qDebug() << QString("[SQL Error] %1: %2)").arg(text).arg(lastError.text()) << "QUERY: " << model->query().executedQuery();
		msgBox.exec();
		return true;
	}
	return false;
}

void SetForeignKeyMeta(const QString& tableName)
{
	QSqlQueryModel query;

	query.setQuery(QString("SELECT\n"
	                       "    tc.table_schema, \n"
	                       "    tc.constraint_name, \n"
	                       "    tc.table_name, \n"
	                       "    kcu.column_name, \n"
	                       "    ccu.table_schema AS foreign_table_schema,\n"
	                       "    ccu.table_name AS foreign_table_name,\n"
	                       "    ccu.column_name AS foreign_column_name \n"
	                       "FROM \n"
	                       "    information_schema.table_constraints AS tc \n"
	                       "    JOIN information_schema.key_column_usage AS kcu\n"
	                       "      ON tc.constraint_name = kcu.constraint_name\n"
	                       "      AND tc.table_schema = kcu.table_schema\n"
	                       "    JOIN information_schema.constraint_column_usage AS ccu\n"
	                       "      ON ccu.constraint_name = tc.constraint_name\n"
	                       "      AND ccu.table_schema = tc.table_schema\n"
	                       "WHERE tc.constraint_type = 'FOREIGN KEY' AND tc.table_name='%1';").arg(
			tableName));
	ShowMessageBoxError("Ошибка при получении информации о внешних ключах", &query);

	TableMetaInfo info;
	for (int i = 0; i < query.columnCount(); i++)
	{
		if (auto record = query.record(i); !record.isEmpty() && !record.isNull("table_name"))
		{
//			qDebug() << tableName << record.field("column_name").value().toString() <<
//				record.field("foreign_table_name").value().toString() <<
//					             record.field("foreign_column_name").value().toString() <<
//							     record.field("foreign_table_name").value().toString();
			info.InsertForeignKeyRelation(record.field("column_name").value().toString(),
			                              QSqlRelation(record.field("foreign_table_name").value().toString(),
			                                           record.field("foreign_column_name").value().toString(),
					                              // Считаем, что название display key будет таким же, как и имя таблицы.
					                                   record.field("foreign_table_name").value().toString()));

		}
	}
	TableMetaInfoHolder::Instance().InsertTableMetaInfo(tableName, std::move(info));
}

QString ReplaceUnderscoreWithSpace(QString str)
{
	str.replace("_", " ");
	return std::move(str);
}

QString ReplaceSpaceWithUnderscore(QString str)
{
	str.replace(" ", "_");
	return std::move(str);
}
