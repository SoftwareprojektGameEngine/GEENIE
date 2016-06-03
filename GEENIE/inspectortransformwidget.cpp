#include "inspectortransformwidget.h"
#include "ui_inspectortransformwidget.h"

InspectorTransformWidget::InspectorTransformWidget(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::InspectorTransformWidget)
{
    ui->setupUi(this);
}

InspectorTransformWidget::~InspectorTransformWidget()
{
    delete ui;
}
