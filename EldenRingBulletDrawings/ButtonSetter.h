#pragma once
#include <QtWidgets>

class ButtonSetter : public QLineEdit
{
	Q_OBJECT

public:
	ButtonSetter(QWidget* pwgt = Q_NULLPTR);
	int getKey();

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	int key;
};

