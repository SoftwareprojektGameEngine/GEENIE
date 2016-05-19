#include "menuebar.h"
#include "ui_menuebar.h"

Menuebar::Menuebar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menuebar)
{
    ui->setupUi(this);
}

Menuebar::~Menuebar()
{
    delete ui;
}
