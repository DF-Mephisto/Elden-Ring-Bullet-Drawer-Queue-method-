#include "LineEdit.h"

LineEdit::LineEdit(QString name, QWidget* pwgt)
	: QWidget(pwgt)
{
	this->name = new QLabel(name);
	value = new QLineEdit();
	this->name->setBuddy(value);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(this->name, 1);
	layout->addWidget(value, 1);
	layout->setContentsMargins(0, 5, 0, 5);

	setLayout(layout);
}

LineEdit::LineEdit(QString name, QValidator* valid, QWidget* pwgt)
	: LineEdit(name, pwgt)
{
	value->setValidator(valid);
}

QString LineEdit::getValue()
{
	return value->text();
}

void LineEdit::setValue(QString value)
{
	this->value->setText(value);
}