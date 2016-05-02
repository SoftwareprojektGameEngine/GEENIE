#include "geeniemainwindow.h"
#include "ui_geeniemainwindow.h"

GEENIEMainWindow::GEENIEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GEENIEMainWindow)
{
    ui->setupUi(this);
}

GEENIEMainWindow::~GEENIEMainWindow()
{
    delete ui;
}
