#include "inspectormaterialwidget.h"
#include "ui_inspectormaterialwidget.h"

InspectorMaterialWidget::InspectorMaterialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorMaterialWidget)
{
    ui->setupUi(this);
}

InspectorMaterialWidget::~InspectorMaterialWidget()
{
    delete ui;
}
