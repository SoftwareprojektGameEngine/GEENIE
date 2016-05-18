#include "assetwidget.h"
#include "ui_assetwidget.h"

AssetWidget::AssetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetWidget)
{
    ui->setupUi(this);
}

AssetWidget::~AssetWidget()
{
    delete ui;
}
