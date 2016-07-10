#include "renameentitydialog.h"
#include "ui_renameentitydialog.h"

RenameEntityDialog::RenameEntityDialog(QWidget *parent, QString name) :
    QDialog(parent),
    _name(name),
    ui(new Ui::RenameEntityDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(name);
}

RenameEntityDialog::~RenameEntityDialog()
{
    delete ui;
}

QString RenameEntityDialog::name()
{
    return _name;
}

void RenameEntityDialog::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        _name = ui->lineEdit->text();
    }
    QDialog::accept();
}

void RenameEntityDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}
