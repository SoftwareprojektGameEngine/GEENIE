#include "newdialog.h"
#include "ui_newdialog.h"

NewDialog::NewDialog(QWidget *parent, bool projectConfigured) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
    ui->listWidget->addItem(QString("Project"));
    if(projectConfigured)
    {
        ui->listWidget->addItem(QString("Scene"));
    }
    _type = true;
}

NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::on_pushButton_clicked()
{
    if(!ui->listWidget->selectedItems().isEmpty())
    {
        if(ui->listWidget->selectedItems().at(0)->text() == QString("Project"))
        {
            _type = true;
        }
        else
        {
            _type = false;
        }
        QDialog::accept();
    }
    else
    {
        return;
    }
}

void NewDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}
