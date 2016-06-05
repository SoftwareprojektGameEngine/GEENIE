#include "inspectormaterialwidget.h"
#include "ui_inspectormaterialwidget.h"

InspectorMaterialWidget::InspectorMaterialWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorMaterialWidget)
{
    ui->setupUi(this);
}

InspectorMaterialWidget::~InspectorMaterialWidget()
{
    delete ui;
}
