#include "layoutform.h"
#include "ui_layoutform.h"

LayoutForm::LayoutForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayoutForm)
{
    ui->setupUi(this);
}

LayoutForm::~LayoutForm()
{
    delete ui;
}
