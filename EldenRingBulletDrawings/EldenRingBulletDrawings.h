#pragma once
#include <QtWidgets>
#include <stdexcept>

#include "ControlMenu.h"
#include "DrawingNet.h"
#include "ButtonSetter.h"
#include "Constants.h"
#include "MemReader.h"
#include "POINT3D.h"

using std::runtime_error;

class EldenRingBulletDrawings : public QWidget
{
    Q_OBJECT

public:
    EldenRingBulletDrawings(QWidget *parent = Q_NULLPTR);

private:
    ControlMenu* controlMenu;
    DrawingNet* drawingNet;
    QPushButton* drawBtn;
    ButtonSetter* buttonSetter;

    MemReader reader;

protected:
    void timerEvent(QTimerEvent* e) override;

private slots:
    void draw();
};
