#include "inspectormaterialwidget.h"
#include "ui_inspectormaterialwidget.h"

InspectorMaterialWidget::InspectorMaterialWidget(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::InspectorMaterialWidget)
{
    ui->setupUi(this);
}

InspectorMaterialWidget::~InspectorMaterialWidget()
{
    delete ui;
}
