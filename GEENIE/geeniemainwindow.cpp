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

void GEENIEMainWindow::on_pushButton_clicked()
{
    DEBUG_MSG(QString("Test DEBUG"));
}

void GEENIEMainWindow::on_pushButton_2_clicked()
{
    ERROR_MSG(QString("Test ERROR"));
}
