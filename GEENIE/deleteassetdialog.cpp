#include "deleteassetdialog.h"
#include "ui_deleteassetdialog.h"

DeleteAssetDialog::DeleteAssetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteAssetDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    if(ui->comboBox->currentIndex() != -1)
    {
        ui->pushButton->setEnabled(true);
        this->assetID = ui->comboBox->currentData().toByteArray();
    }
}

DeleteAssetDialog::~DeleteAssetDialog()
{
    delete ui;
}

void DeleteAssetDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

void DeleteAssetDialog::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex() != -1)
    {
        QDialog::accept();
    }
    else
    {
        QDialog::reject();
    }
}

void DeleteAssetDialog::setAssetList(QList<ASSET_LIST_DA> list)
{
    for(int i=0; i<list.size(); i++)
    {
        ui->comboBox->addItem(list.at(i).name, list.at(i).id.toByteArray());
    }
}

QUuid DeleteAssetDialog::getAssetID()
{
    return this->assetID;
}

void DeleteAssetDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex() != -1)
    {
        ui->pushButton->setEnabled(true);
        this->assetID = ui->comboBox->currentData().toByteArray();
    }
}
