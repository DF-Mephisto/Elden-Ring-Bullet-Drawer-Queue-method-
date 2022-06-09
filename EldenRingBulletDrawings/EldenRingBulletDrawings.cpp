#include "EldenRingBulletDrawings.h"

EldenRingBulletDrawings::EldenRingBulletDrawings(QWidget* parent)
    : QWidget(parent)
{
    QLocale::setDefault(QLocale(QLocale::English));
    setWindowTitle("Elden Ring Bullet Drawer @By Mephisto");

    resize(503, 745);

    QFile styleFile(":/EldenRingBulletDrawings/style");
    styleFile.open(QIODevice::ReadOnly);
    QString style(styleFile.readAll());
    setStyleSheet(style);

    setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(QPixmap(":/EldenRingBulletDrawings/space")));
    setPalette(pal);

    controlMenu = new ControlMenu();
    drawingNet = new DrawingNet(BLOCKSIZE);

    QScrollArea* netSA = new QScrollArea();
    netSA->setWidget(drawingNet);

    drawBtn = new QPushButton("Draw");
    drawBtn->setFixedHeight(40);
    buttonSetter = new ButtonSetter();
    buttonSetter->setPlaceholderText("Hotkey");
    buttonSetter->setFixedHeight(40);
    QFont font = buttonSetter->font();
    font.setPointSizeF(18);
    buttonSetter->setFont(font);
    buttonSetter->setAlignment(Qt::AlignCenter);

    QHBoxLayout* drawLayout = new QHBoxLayout();
    drawLayout->addWidget(buttonSetter, 2);
    drawLayout->addWidget(drawBtn, 3);
    drawLayout->setContentsMargins(10, 10, 10, 10);
    drawLayout->setSpacing(20);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(controlMenu);
    layout->addWidget(netSA);
    layout->addLayout(drawLayout);
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    connect(controlMenu, SIGNAL(netSizeChanged(int, int, int)), drawingNet, SLOT(netSizeChanged(int, int, int)));
    connect(controlMenu, SIGNAL(currentLayerChanged(int)), drawingNet, SLOT(currentLayerChanged(int)));
    connect(drawBtn, SIGNAL(clicked()), this, SLOT(draw()));

    controlMenu->setNetSize();
    startTimer(100);
}

void EldenRingBulletDrawings::timerEvent(QTimerEvent* e)
{
    //VK_NUMPAD0
    if (GetAsyncKeyState(buttonSetter->getKey()) & 1)
    {
        if (reader.getProcessStatus())
                draw();
    }
}

void EldenRingBulletDrawings::draw()
{
    DWORD32 bulletId;
    float space;
    bool*** net;

    try
    {
        if (!reader.initialize())
            throw runtime_error("Can't find Elden Ring process");

        bulletId = controlMenu->getBulletId();
        space = controlMenu->getSpace();
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error", e.what());
        return;
    }

    net = drawingNet->getNet();
    int xSize = controlMenu->getX();
    int ySize = controlMenu->getY();
    int zSize = controlMenu->getZ();

    float angle = reader.getCharAngle();
    POINT3D pos = reader.getCharPos();

    reader.lockSpawning();
    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            for (int x = 0; x < xSize; x++)
            {
                if (net[z][y][x])
                {
                    float xCoord = (float)(xSize - x) * space - xSize * space / 2;
                    float yCoord = (float)(ySize - y) * space + 1.5f;
                    float zCoord = (float)z * space;
                    
                    fPOINT horPos = VectorTransformer::rotate2D(angle, fPOINT{ xCoord, zCoord });
                    xCoord = horPos.x;
                    zCoord = horPos.y;

                    xCoord += pos.x;
                    yCoord += pos.y;
                    zCoord += pos.z;

                    reader.spawnBullet(bulletId, xCoord, yCoord, zCoord, -sin(angle), 0, -cos(angle));
                }
            }
        }
    }
    reader.unlockSpawning();
}