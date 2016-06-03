#include "inspectoraudiowidget.h"
#include "ui_inspectoraudiowidget.h"

InspectorAudioWidget::InspectorAudioWidget(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::InspectorAudioWidget)
{
    ui->setupUi(this);
}

InspectorAudioWidget::~InspectorAudioWidget()
{
    delete ui;
}
