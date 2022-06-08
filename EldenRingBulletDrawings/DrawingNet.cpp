#include "DrawingNet.h"

DrawingNet::DrawingNet(int blockSize, QWidget* pwgt)
	: QWidget(pwgt), 
	blockSize(blockSize)
{
	xSize = 0;
	ySize = 0;
	zSize = 0;
	currentLayer = 0;
	net = nullptr;
}

DrawingNet::~DrawingNet()
{
	clearNet();
}

void DrawingNet::netSizeChanged(int xSize, int ySize, int zSize)
{
	clearNet();
	initNet(xSize, ySize, zSize);

	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;
	setFixedSize(xSize * blockSize + 1, ySize * blockSize + 1);

	currentLayer = 0;
	repaint();
}

void DrawingNet::clearNet()
{
	for (int z = 0; z < zSize; z++)
	{
		for (int y = 0; y < ySize; y++)
		{
			delete[] net[z][y];
		}
		delete[] net[z];
	}
	delete[] net;
}

void DrawingNet::initNet(int xSize, int ySize, int zSize)
{
	net = new bool** [zSize];
	for (int z = 0; z < zSize; z++)
	{
		net[z] = new bool* [ySize];

		for (int y = 0; y < ySize; y++)
		{
			net[z][y] = new bool[xSize] {false};
		}
	}
}

bool*** DrawingNet::getNet()
{
	return net;
}

void DrawingNet::currentLayerChanged(int layer)
{
	if (layer < 0)
		return;

	currentLayer = layer;
	repaint();
}

void DrawingNet::mousePressEvent(QMouseEvent* e)
{
	int x = e->pos().x() / blockSize;
	int y = e->pos().y() / blockSize;
	if (x >= xSize || y >= ySize)
		return;

	net[currentLayer][y][x] = !net[currentLayer][y][x];
	repaint();
}

void DrawingNet::paintEvent(QPaintEvent* e)
{
	static QPixmap light = QPixmap(":/EldenRingBulletDrawings/light").scaled(blockSize, blockSize);

	QPainter p(this);
	p.setPen(QPen(qRgb(128, 128, 128)));

	for (int i = 0; i <= xSize; i++)
		p.drawLine(i * blockSize, 0, i * blockSize, height());
	for (int i = 0; i <= ySize; i++)
		p.drawLine(0, i * blockSize, width(), i * blockSize);

	for (int y = 0; y < ySize; y++)
		for (int x = 0; x < xSize; x++)
			if (net[currentLayer][y][x])
				p.drawPixmap(x * blockSize, y * blockSize, blockSize, blockSize, light);
}