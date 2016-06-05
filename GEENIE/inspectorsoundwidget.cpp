#include "inspectorsoundwidget.h"
#include "ui_inspectorsoundwidget.h"

InspectorSoundWidget::InspectorSoundWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorSoundWidget)
{
    ui->setupUi(this);
}

InspectorSoundWidget::~InspectorSoundWidget()
{
    delete ui;
}
