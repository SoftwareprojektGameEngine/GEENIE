#include "inspectorcamerawidget.h"
#include "ui_inspectorcamerawidget.h"

InspectorCameraWidget::InspectorCameraWidget(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::InspectorCameraWidget)
{
    ui->setupUi(this);
}

InspectorCameraWidget::~InspectorCameraWidget()
{
    delete ui;
}
