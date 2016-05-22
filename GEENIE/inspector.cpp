#include "inspector.h"
#include "ui_inspector.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);
}

Inspector::~Inspector()
{
    delete ui;
}
