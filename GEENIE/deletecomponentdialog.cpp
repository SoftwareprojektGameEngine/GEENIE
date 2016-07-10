#include "deletecomponentdialog.h"
#include "ui_deletecomponentdialog.h"

DeleteComponentDialog::DeleteComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteComponentDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);

    if(ui->comboBox->currentIndex() !=-1)
    {
        ui->pushButton->setEnabled(true);
        this->selectedId = ui->comboBox->currentData(Qt::UserRole).toByteArray();
    }
}

DeleteComponentDialog::~DeleteComponentDialog()
{
    delete ui;
}

void DeleteComponentDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

void DeleteComponentDialog::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex() != -1)
    {
        QDialog::accept();
    }
}

void DeleteComponentDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex() !=-1)
    {
        ui->pushButton->setEnabled(true);
        this->selectedId = ui->comboBox->currentData(Qt::UserRole).toByteArray();
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}

void DeleteComponentDialog::SetComponentList(QList<COMPONENT_DATA_DC> list)
{
    this->data = list;
    for(int i=0;i<list.size();i++)
    {
        ui->comboBox->addItem(list.at(i).name,list.at(i).id.toByteArray());
    }
}
