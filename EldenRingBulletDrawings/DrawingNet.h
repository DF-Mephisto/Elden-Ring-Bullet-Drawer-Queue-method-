#pragma once
#include <QtWidgets>

class DrawingNet : public QWidget
{
	Q_OBJECT

public:
	DrawingNet(int blockSize, QWidget* pwgt = Q_NULLPTR);
	~DrawingNet();
	bool*** getNet();

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void paintEvent(QPaintEvent* e) override;

private:
	int xSize;
	int ySize;
	int zSize;
	int currentLayer;
	bool*** net;

	int blockSize;

private:
	void clearNet();
	void initNet(int xSize, int ySize, int zSize);

private slots:
	void netSizeChanged(int xSize, int ySize, int zSize);
	void currentLayerChanged(int layer);
};

