#include "PropertyInspectorFactory.h"

std::pair<QWidget*, QLabel*> CreateLabelWidget(QWidget* parent, const QString& name)
{
	auto labelHolder = new QWidget();
	auto labelLayout = new QHBoxLayout();
	labelHolder->setLayout(labelLayout);

	auto label = new QLabel();
	label->setText(ReplaceUnderscoreWithSpace(name));

	labelLayout->addWidget(label);

	if (auto parentLayout = parent->layout())
	{
		parentLayout->addWidget(labelHolder);
	}
	else
	{
		assert("NoParentLayout");
	}

	return {labelHolder, label};
}

bool PropertyInspectorFactory::RegisterInFactory(QVariant::Type type,
                                                 PropertyInspectorFactory::PropertyCtor handler)
{
	if (auto iter = ctors.find(type); iter == ctors.end())
	{
		ctors.insert(type, handler);
		return true;
	}
	return false;
}

IProperty::Ptr PropertyInspectorFactory::CreateProperty(QWidget* parent, const QSqlField& field)
{
	if (auto ctorIter = ctors.find(field.type()); ctorIter != ctors.end())
	{
		// Создаём label.
		auto&&[labelHolder, label] = CreateLabelWidget(parent, field.name());
		// Создаём сам property.
		auto property = ctorIter.value()();
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
	assert(!"Can't find default constructor");
	return nullptr;
}

