#include "newprojectwidget.h"
#include "ui_newprojectwidget.h"

NewProjectWidget::NewProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProjectWidget)
{
    ui->setupUi(this);
}

NewProjectWidget::~NewProjectWidget()
{
    delete ui;
}
