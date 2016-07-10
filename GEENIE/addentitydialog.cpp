#include "addentitydialog.h"
#include "ui_addentitydialog.h"

AddEntityDialog::AddEntityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEntityDialog)
{
    _name = QString();
    ui->setupUi(this);
}

AddEntityDialog::~AddEntityDialog()
{
    delete ui;
}

void AddEntityDialog::on_pushButton_clicked()
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

void AddEntityDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}
