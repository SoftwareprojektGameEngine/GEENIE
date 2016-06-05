#include "inspectorscriptcomponent.h"
#include "ui_inspectorscriptcomponent.h"

InspectorScriptComponent::InspectorScriptComponent(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    ui(new Ui::InspectorScriptComponent)
{
    ui->setupUi(this);
}

InspectorScriptComponent::~InspectorScriptComponent()
{
    delete ui;
}
