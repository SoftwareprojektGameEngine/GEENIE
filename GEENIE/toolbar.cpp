#include "toolbar.h"
#include "ui_toolbar.h"

Toolbar::Toolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Toolbar)
{
    ui->setupUi(this);
}

Toolbar::~Toolbar()
{
    delete ui;
}
