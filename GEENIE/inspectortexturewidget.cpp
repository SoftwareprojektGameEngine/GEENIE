#include "inspectortexturewidget.h"
#include "ui_inspectortexturewidget.h"

InspectorTextureWidget::InspectorTextureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorTextureWidget)
{
    ui->setupUi(this);
}

InspectorTextureWidget::~InspectorTextureWidget()
{
    delete ui;
}
