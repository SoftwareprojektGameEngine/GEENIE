#include "inspectorcamerawidget.h"
#include "ui_inspectorcamerawidget.h"

InspectorCameraWidget::InspectorCameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorCameraWidget)
{
    ui->setupUi(this);
}

InspectorCameraWidget::~InspectorCameraWidget()
{
    delete ui;
}
