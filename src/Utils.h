#ifndef BDCOURSE_UTILS_H
#define BDCOURSE_UTILS_H

template<typename T>
class Singleton
{
protected:
	Singleton() = default;
	Singleton(Singleton&&) = delete;
	Singleton(const Singleton&) = delete;
public:
	static T& Instance()
	{
		static T* instance = new T();
		return *instance;
	}
};

QVector<QString> GetDBTablesHeaders();
QString RowToString(QSqlTableModel* model, int index);
QString PrimaryKeyName(QSqlTableModel* model);

void SetForeignKeyMeta(const QString& tableName);
QString ReplaceUnderscoreWithSpace(QString str);
QString ReplaceSpaceWithUnderscore(QString str);

bool ShowMessageBoxError(const QString& text, QSqlQueryModel* model = nullptr);

#endif //BDCOURSE_UTILS_H
