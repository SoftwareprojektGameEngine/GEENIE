#include "sceneeditwidget.h"
#include "ui_sceneeditwidget.h"
#include <QDebug>
#include <cmath>

Vector rotateVector(const Vector& vec, const Vector& base, const Vector& axis, float radians) {
    Vector result;

    float L = vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
    result.x = ((base.x*(axis.y*axis.y + axis.z*axis.z)-axis.x*(base.y*axis.y + base.z*axis.z - axis.x*vec.x - axis.y*vec.y - axis.z*vec.z)) * (1-cos(radians)) + L*vec.x*cos(radians) + sqrt(L)*(-base.z*axis.y + base.y*axis.z - axis.z*vec.y + axis.y*vec.z)*sin(radians))/L;
    result.y = ((base.y*(axis.x*axis.x + axis.z*axis.z)-axis.y*(base.x*axis.x + base.z*axis.x - axis.x*vec.x - axis.y*vec.y - axis.z*vec.z)) * (1-cos(radians)) + L*vec.y*cos(radians) + sqrt(L)*(base.z*axis.x - base.x*axis.z + axis.z*vec.x - axis.x*vec.z)*sin(radians))/L;
    result.z = ((base.z*(axis.x*axis.x + axis.y*axis.y)-axis.z*(base.x*axis.x + base.y*axis.y - axis.x*vec.x - axis.y*vec.y - axis.z*vec.z)) * (1-cos(radians)) + L*vec.z*cos(radians) + sqrt(L)*(-base.y*axis.x + base.x*axis.y - axis.y*vec.x + axis.x*vec.y)*sin(radians))/L;
    result.w = 1.0f;

    return result;
}

Vector addVector(const Vector& vec1, const Vector& vec2) {
    return Vector(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z, vec1.w+vec2.w);
}

SceneEditWidget::SceneEditWidget(GEENIE* geenie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneEditWidget)
{
    ui->setupUi(this);

    camPos = Vector(0.0f,0.0f,0.0f,1.0f);
    camDir = Vector(1.0f,0.0f,0.0f,0.0f);
    camUp = Vector(0.0f,1.0f,0.0f,0.0f);

    this->engine = geenie->getEngine();
    this->engineWidget = engine->CreateWidget();

    ui->verticalLayout->addWidget(engineWidget->GetWidget());
    /*engineWidget->GetWidget()->setParent(this->ui->frame);
    engineWidget->GetWidget()->setGeometry(this->findChild<QFrame*>(QString("frame"))->geometry());
    engineWidget->GetWidget()->setVisible(true);*/
    //this->grabKeyboard();
    this->engineWidget->SetCamera(camPos, addVector(camPos, camDir), camUp);
}

void SceneEditWidget::keyPressEvent(QKeyEvent *keyEvent) {
    /*switch(keyEvent->key()) {
    case Qt::Key_W: // move forwards
        camPos.x = camPos.x + camDir.x * 0.1f;
        camPos.y = camPos.y + camDir.y * 0.1f;
        camPos.z = camPos.z + camDir.z * 0.1f;
        break;
    case Qt::Key_S: // move backwards
        camPos.x = camPos.x - camDir.x * 0.1f;
        camPos.y = camPos.y - camDir.y * 0.1f;
        camPos.z = camPos.z - camDir.z * 0.1f;
        break;
    case Qt::Key_A: // rotate left
        camDir = rotateVector(camDir, camPos, camUp, 0.05f);
        break;
    case Qt::Key_D: // rotate right
        camDir = rotateVector(camDir, camPos, camUp, -0.05f);
        break;
    case Qt::Key_Q: // move up
        camPos.x = camPos.x + camUp.x * 0.1f;
        camPos.y = camPos.y + camUp.y * 0.1f;
        camPos.z = camPos.z + camUp.z * 0.1f;
        break;
    case Qt::Key_E: // move down
        camPos.x = camPos.x - camUp.x * 0.1f;
        camPos.y = camPos.y - camUp.y * 0.1f;
        camPos.z = camPos.z - camUp.z * 0.1f;
        break;
    }
    engineWidget->SetCamera(camPos, addVector(camPos, camDir), camUp);
    qDebug() << "cam pos: " << camPos.x << " / " << camPos.y << " / " << camPos.z;
    qDebug() << "cam dir: " << camDir.x << " / " << camDir.y << " / " << camDir.z;
    qDebug() << "cam up:  " << camUp.x << " / " << camUp.y << " / " << camUp.z;*/
}

SceneEditWidget::~SceneEditWidget()
{
    delete engineWidget;
    delete ui;
}
