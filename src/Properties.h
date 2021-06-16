#ifndef BDCOURSE_PROPERTIES_H
#define BDCOURSE_PROPERTIES_H

#include "PropertyInspectorFactory.h"

/*
 * Враппер вокруг Property для обобщённого редактирования модели
 */
class Properties
{
public:
	using ForEachHandler = std::function<void(const IProperty::Ptr&)>;
	using PropertiesContainer = QVector<IProperty::Ptr>;
public:
	explicit Properties(QSqlTableModel* model);


	// Создаёт Property с пустыми значениями и помещает их в layout родителя
	void CreateProperties(QWidget* parent);
	// Создаёт Property по рекорду из модели и помещает их в layout родителя
	void CreatePropertiesForRecord(QWidget* parent, int recordIndex);

	// Выставляет значения из Properties в модель
	void SetPropertiesValueToRecord(int recordIndex);
	// Выставляет значения в Property из модели
	void FillPropertiesFromRecord(int recordIndex);

	void ForEachProperty(const ForEachHandler& handler);
	PropertiesContainer& GetProperties() { return properties; };

	IProperty::Ptr GetPropertyWithName(const QString& name);

	int Size() const { return properties.size(); }
	int ModelSize() const { return model->rowCount(); }

	QSqlTableModel* GetModel() const { return model; }

private:
	void CreateProperties(QWidget* parent, const QSqlRecord& record);
private:
	QSqlTableModel* model;
	PropertiesContainer properties{};
};


#endif //BDCOURSE_PROPERTIES_H
