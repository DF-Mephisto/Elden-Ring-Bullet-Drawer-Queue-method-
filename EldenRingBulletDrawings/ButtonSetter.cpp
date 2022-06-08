#include "ButtonSetter.h"

ButtonSetter::ButtonSetter(QWidget* pwgt)
	: QLineEdit(pwgt), key(-1)
{
	setReadOnly(true);
}

void ButtonSetter::keyPressEvent(QKeyEvent* e)
{
	key = e->nativeVirtualKey();
	setText(QKeySequence(e->key()).toString());
}

int ButtonSetter::getKey()
{
	return key;
}