#include "assetwindow.h"
#include "ui_assetwindow.h"

AssetWindow::AssetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssetWindow)
{
    ui->setupUi(this);
}

AssetWindow::~AssetWindow()
{
    delete ui;
}
