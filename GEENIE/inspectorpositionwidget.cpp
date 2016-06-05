#include "inspectorpositionwidget.h"
#include "ui_inspectorpositionwidget.h"

InspectorPositionWidget::InspectorPositionWidget(QWidget *parent,Vector vector, QUuid id, QUuid parentId, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    _vector(vector),
    ui(new Ui::InspectorPositionWidget)
{
    ui->setupUi(this);
    ui->xSpin->setValue(_vector.x);
    ui->ySpin->setValue(_vector.y);
    ui->zSpin->setValue(_vector.z);
    ui->wSpin->setValue(_vector.w);
    ui->lineEdit->setText(_name);
}

InspectorPositionWidget::~InspectorPositionWidget()
{
    delete ui;
}

void InspectorPositionWidget::on_xSpin_valueChanged(double arg1)
{
    _vector.x = arg1;
}

void InspectorPositionWidget::on_ySpin_valueChanged(double arg1)
{
    _vector.y = arg1;
}

void InspectorPositionWidget::on_zSpin_valueChanged(double arg1)
{
    _vector.z = arg1;
}

void InspectorPositionWidget::on_wSpin_valueChanged(double arg1)
{
    _vector.w = arg1;
}

void InspectorPositionWidget::on_appBtn_clicked()
{
    emit applyPosition(_vector,_id,_parentId,ui->lineEdit->text());
}
