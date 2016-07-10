#include "addscenedialog.h"
#include "ui_addscenedialog.h"

AddSceneDialog::AddSceneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSceneDialog)
{
    ui->setupUi(this);
}

AddSceneDialog::~AddSceneDialog()
{
    delete ui;
}

void AddSceneDialog::on_pushButton_clicked()
{
    _name = ui->lineEdit->text();
    if(_name.isEmpty())
    {
        QDialog::reject();
    }
    else
    {
        QDialog::accept();
    }
}

void AddSceneDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}
