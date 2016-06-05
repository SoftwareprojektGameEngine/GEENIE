#include "inspectortexturewidget.h"
#include "ui_inspectortexturewidget.h"

InspectorTextureWidget::InspectorTextureWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorTextureWidget)
{
    ui->setupUi(this);
}

InspectorTextureWidget::~InspectorTextureWidget()
{
    delete ui;
}
