#pragma once
#include <QtWidgets>
#include <stdexcept>

#include "LineEdit.h"

class ControlMenu : public QWidget
{
	Q_OBJECT

public:
	ControlMenu(QWidget* pwgt = Q_NULLPTR);
	int getBulletId();
	float getSpace();
	int getX();
	int getY();
	int getZ();

protected:
	void paintEvent(QPaintEvent* e) override;

private:
	LineEdit* bulletId;
	LineEdit* space;
	LineEdit* xSize;
	LineEdit* ySize;
	LineEdit* zSize;
	QComboBox* currentLayer;
	QPushButton* set;

	void fillZSize();

public slots:
	void setNetSize();

signals:
	void netSizeChanged(int xSize, int ySize, int zSize);
	void currentLayerChanged(int layer);
};

