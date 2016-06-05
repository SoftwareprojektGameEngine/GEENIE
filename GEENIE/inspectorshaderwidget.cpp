#include "inspectorshaderwidget.h"
#include "ui_inspectorshaderwidget.h"

InspectorShaderWidget::InspectorShaderWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorShaderWidget)
{
    ui->setupUi(this);
}

InspectorShaderWidget::~InspectorShaderWidget()
{
    delete ui;
}
