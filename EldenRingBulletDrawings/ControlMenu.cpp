#include "ControlMenu.h"

ControlMenu::ControlMenu(QWidget* pwgt)
	: QWidget(pwgt)
{
	bulletId = new LineEdit("Bullet ID: ", new QIntValidator());
	space = new LineEdit("Drawing size: ", new QDoubleValidator());
	xSize = new LineEdit("Horizontal size: ", new QRegExpValidator(QRegExp("[1-9][0-9]{,2}")));
	ySize = new LineEdit("Vertical size: ", new QRegExpValidator(QRegExp("[1-9][0-9]{,2}")));
	zSize = new LineEdit("Layers: ", new QRegExpValidator(QRegExp("[1-9][0-9]{,2}")));
	bulletId->setValue("10511000");
	space->setValue("0.3");
	xSize->setValue("10");
	ySize->setValue("10");
	zSize->setValue("1");

	currentLayer = new QComboBox();
	set = new QPushButton("Set");
	set->setFixedWidth(100);

	QHBoxLayout* sizeLayout = new QHBoxLayout();
	sizeLayout->addWidget(xSize);
	sizeLayout->addWidget(ySize);
	sizeLayout->addWidget(zSize);
	sizeLayout->setSpacing(40);

	QLabel* currentLayerLabel = new QLabel("Current layer: ");
	QHBoxLayout* footerLayout = new QHBoxLayout();
	footerLayout->addWidget(currentLayerLabel, 0.7);
	footerLayout->addWidget(currentLayer, 1);
	footerLayout->addWidget(set, 0.7);
	footerLayout->setSpacing(30);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(bulletId);
	layout->addWidget(space);
	layout->addLayout(sizeLayout);
	layout->addLayout(footerLayout);
	layout->setAlignment(Qt::AlignTop);

	setLayout(layout);
	setNetSize();

	connect(set, &QPushButton::clicked, this, &ControlMenu::setNetSize);
	connect(currentLayer, qOverload<int>(&QComboBox::currentIndexChanged), this, &ControlMenu::currentLayerChanged);
}

int ControlMenu::getBulletId()
{
	bool status = false;
	int res = bulletId->getValue().toInt(&status);
	if (!status)
		throw std::runtime_error("Wrong Bullet ID value");

	return res;

}

float ControlMenu::getSpace()
{
	bool status = false;
	float res = space->getValue().toFloat(&status);
	if (!status)
		throw std::runtime_error("Wrong space value");

	return res;
}

void ControlMenu::setNetSize()
{
	fillZSize();
	emit netSizeChanged(xSize->getValue().toInt(), 
		ySize->getValue().toInt(),
		zSize->getValue().toInt());
}

void ControlMenu::fillZSize()
{
	currentLayer->clear();
	
	int size = zSize->getValue().toInt();
	for (int i = 1; i <= size; i++)
	{
		currentLayer->addItem(QString::number(i));
	}
}

void ControlMenu::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

int ControlMenu::getX()
{
	return xSize->getValue().toInt();
}

int ControlMenu::getY()
{
	return ySize->getValue().toInt();
}

int ControlMenu::getZ()
{
	return zSize->getValue().toInt();
}