#include "inspectortexturewidget.h"
#include "ui_inspectortexturewidget.h"

InspectorTextureWidget::InspectorTextureWidget(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::InspectorTextureWidget)
{
    ui->setupUi(this);
}

InspectorTextureWidget::~InspectorTextureWidget()
{
    delete ui;
}
