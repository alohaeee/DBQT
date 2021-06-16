#ifndef BDCOURSE_PROPERTYINSPECTORFACTORY_H
#define BDCOURSE_PROPERTYINSPECTORFACTORY_H

#include "Utils.h"

/*
 * Интерфейс к редактированию SQL поля
 */
class IProperty : public std::enable_shared_from_this<IProperty>
{
public:
	using Ptr = std::shared_ptr<IProperty>;
public:
	virtual void SetValue(const QVariant& value) = 0;
	[[nodiscard]] virtual QVariant GetValue() const = 0;

	virtual void Clear() = 0;

	[[nodiscard]] virtual bool IsEmpty() const = 0;

	virtual QWidget* GetWidget() const = 0;

	virtual void SetLabel(QLabel* label) = 0;
	virtual QLabel* GetLabel() const = 0;

	virtual void SetName(const QString& name) = 0;
	virtual const QString& GetName() const = 0;

	using OnEditHandler = std::function<void(const IProperty::Ptr& property)>;
	virtual void SetOnEditHandler(const OnEditHandler& handler) = 0;
};

/*
 * Фабрика, создающая редакторы из SQL поля.
 */
class PropertyInspectorFactory
{
public:
	using PropertyCtor = std::function<IProperty::Ptr()>;
public:
	// Регистрация в фабрике по типу лежащему в варианте. Если на такой тип уже существует редактор, то возвращает false.
	static bool RegisterInFactory(QVariant::Type type, PropertyCtor handler);

	template<typename TProperty, typename TValue>
	static bool RegisterInFactory()
	{
		auto typeId = qMetaTypeId<TValue>();
		if (auto iter = ctors.find(typeId); iter == ctors.end())
		{
			ctors.insert(typeId, []() {
				return IProperty::Ptr(new TProperty{});
			});
			return true;
		}
		//assert (!"Already registered");
		return false;
	}

	template<typename T>
	static typename std::shared_ptr<T> CustomCreateProperty(QWidget* parent, const QSqlField& field)
	{
		// Создаём label.
		auto&&[labelHolder, label] = CreateLabelWidget(parent, field.name());
		// Создаём сам property.
		auto property = std::make_shared<T>();
		property->SetName(field.name());
		property->SetLabel(label);
		// Widget Property храним рядом с лейблом. В их общем layout
		if (auto layoutHolder = labelHolder->layout())
		{
			layoutHolder->addWidget(property->GetWidget());
		}
		// Выставляем значение.
		property->SetValue(field.value());
		return property;
	}
	// Создаёт редактор для заданного sql поля, кладя его в layout родителя.
	static IProperty::Ptr CreateProperty(QWidget* parent, const QSqlField& field);
private:
	static inline QMap<int, PropertyCtor> ctors = {};
};

template<typename TProperty, typename TValue, typename TWidget>
class CRTPProperty : public IProperty
{
public:
	using PropertyType = TProperty;
	using ValueType = TValue;
	using WidgetType = TWidget;
public:
	static bool IsRegistered()
	{ return isRegistered; }

public:
	CRTPProperty() = default;
	virtual ~CRTPProperty() = default;

	void SetValue(const QVariant& value) override
	{
		if (value.template canConvert<ValueType>())
		{
			SetTypedValue(value.template value<ValueType>());
		}
		else
		{
			assert(!"Can't convert to type");
		}
	}

	QVariant GetValue() const override
	{
		return GetTypedValue();
	}

	void Clear() override
	{ SetTypedValue(ValueType{}); }

	bool IsEmpty() const override
	{ return GetTypedValue() == ValueType{}; }

	virtual void SetTypedValue(ValueType&& value) = 0;
	virtual ValueType GetTypedValue() const = 0;


	QWidget* GetWidget() const override
	{ return widget; }

	void SetLabel(QLabel* label) override
	{ this->label = label; }

	QLabel* GetLabel() const override
	{ return label; }

	void SetName(const QString& name) override
	{ this->name = name; }

	const QString& GetName() const override
	{ return name; }

	WidgetType* GetTypedWidget() const
	{ return widget; }

protected:
	int recordIndex = -1;
	QString name{};
	WidgetType* widget = new WidgetType();
	QLabel* label = nullptr;
private:
	// Регистрируемся в фабрике. Если уже был
	static inline bool isRegistered = PropertyInspectorFactory::RegisterInFactory<PropertyType, ValueType>();
};


class StringProperty : public CRTPProperty<StringProperty, QString, QLineEdit>
{
public:
	void SetTypedValue(QString&& value) override
	{
		widget->setText(value);
	}

	QString GetTypedValue() const override
	{
		return widget->text();
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, &QLineEdit::textChanged, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
};

class TextProperty : public CRTPProperty<TextProperty, QString, QTextEdit>
{
public:
	void SetTypedValue(QString&& value) override
	{
		widget->setText(value);
	}

	QString GetTypedValue() const override
	{
		return widget->toPlainText();
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, &QTextEdit::textChanged, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
};
class IntProperty : public CRTPProperty<IntProperty, int, QSpinBox>
{
public:
	void SetTypedValue(int&& value) override
	{
		widget->setValue(value);
	}

	int GetTypedValue() const override
	{
		return widget->value();
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, (void(QSpinBox::*)(int))&QSpinBox::valueChanged, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
};

class ForeignKeyProperty : public CRTPProperty<ForeignKeyProperty, int, QComboBox>
{
public:
	static IProperty::Ptr Create(QWidget* parent, const QSqlField& field, const QStringList& vals, const QList<int>& index)
	{
		auto property = PropertyInspectorFactory::CustomCreateProperty<ForeignKeyProperty>(parent, field);
		property->index = index;
		property->widget->addItems(vals);

		return property;
	}

	void SetTypedValue(int&& value) override
	{
		widget->setCurrentIndex(value);
	}

	int GetTypedValue() const override
	{
		return index[widget->currentIndex()];
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, (void(QComboBox::*)(int))&QComboBox::currentIndexChanged, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
private:
	QList<int> index;
};



class DateProperty : public CRTPProperty<DateProperty, QDate, QDateEdit>
{
public:
	void SetTypedValue(QDate&& value) override
	{
		widget->setDate(value);
	}

	QDate GetTypedValue() const override
	{
		return widget->date();
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, &QDateEdit::dateChanged, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
};

class BooleanProperty : public CRTPProperty<BooleanProperty, bool, QCheckBox>
{
public:
	void SetTypedValue(bool&& value) override
	{
		if (GetTypedValue() != value)
		{
			widget->toggle();
		}
	}

	bool GetTypedValue() const override
	{
		return widget->isChecked();
	}
	void SetOnEditHandler(const OnEditHandler& handler) override
	{
		widget->connect(widget, &QCheckBox::pressed, [handler, this](){
			auto ptr = shared_from_this();
			if (ptr)
			{
				handler(ptr);
			}
		});
	}
};

inline std::pair<QWidget*, QLabel*> CreateLabelWidget(QWidget* parent, const QString& name);

class TableMetaInfo
{
public:
	void InsertForeignKeyRelation(const QString& field, const QSqlRelation& relation)
	{
		foreignKeyRelation[field] = relation;
	}

	std::optional<QSqlRelation> GetKeyRelation(const QString& field) const
	{
		if (auto iter = foreignKeyRelation.find(field); iter != foreignKeyRelation.end())
		{
			return iter->second;
		}
		return std::nullopt;
	}
	std::optional<QSqlRelation> GetKeyRelationByDisplay(const QString& field) const
	{
		auto iter = std::find_if(foreignKeyRelation.begin(), foreignKeyRelation.end(), [field](const auto& iter){
			return iter.second.displayColumn() == field;
		});
		if (iter != foreignKeyRelation.end())
		{
			return iter->second;
		}
		return std::nullopt;
	}
	bool HasKeyRelation(const QString& field) const
	{
		return foreignKeyRelation.find(field) != foreignKeyRelation.end();
	}

	const auto& GetForeignKeyRelation() const { return foreignKeyRelation; }

	bool IsEmpty() const
	{
		return foreignKeyRelation.empty();
	}
	explicit operator bool()
	{
		return !IsEmpty();
	}
	//void InsertСustomProperty(const QString& field, const PropertyInspectorFactory::PropertyCtor& ctor);

private:
	std::map<QString, QSqlRelation> foreignKeyRelation;
	QMap<QString, PropertyInspectorFactory::PropertyCtor> customPropertyForField;
};

class TableMetaInfoHolder : public Singleton<TableMetaInfoHolder>
{
public:
	void InsertTableMetaInfo(const QString& table, TableMetaInfo&& tableMetaInfo)
	{
		tablesInfos[table] = tableMetaInfo;
	}

	TableMetaInfo& GetTableMetaInfo(const QString& table)
	{
		return tablesInfos[table];
	}

private:
	QMap<QString, TableMetaInfo> tablesInfos;
};


#endif //BDCOURSE_PROPERTYINSPECTORFACTORY_H
