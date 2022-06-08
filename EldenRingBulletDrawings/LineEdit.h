#pragma once
#include <QtWidgets>

class LineEdit : public QWidget
{
	Q_OBJECT

public:
	LineEdit(QString name, QWidget* pwgt = Q_NULLPTR);
	LineEdit(QString name, QValidator* valid, QWidget* pwgt = Q_NULLPTR);

	QString getValue();
	void setValue(QString value);

private:
	QLabel* name;
	QLineEdit* value;
};

