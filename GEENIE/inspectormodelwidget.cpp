#include "inspectormodelwidget.h"
#include "ui_inspectormodelwidget.h"

InspectorModelWidget::InspectorModelWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorModelWidget)
{
    ui->setupUi(this);
}

InspectorModelWidget::~InspectorModelWidget()
{
    delete ui;
}
