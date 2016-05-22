#include "inspectortransformwidget.h"
#include "ui_inspectortransformwidget.h"

InspectorTransformWidget::InspectorTransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorTransformWidget)
{
    ui->setupUi(this);
}

InspectorTransformWidget::~InspectorTransformWidget()
{
    delete ui;
}
