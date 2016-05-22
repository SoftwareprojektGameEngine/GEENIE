#include "inspectoraudiowidget.h"
#include "ui_inspectoraudiowidget.h"

InspectorAudioWidget::InspectorAudioWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorAudioWidget)
{
    ui->setupUi(this);
}

InspectorAudioWidget::~InspectorAudioWidget()
{
    delete ui;
}
