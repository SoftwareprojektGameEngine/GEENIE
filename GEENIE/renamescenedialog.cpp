#include "renamescenedialog.h"
#include "ui_renamescenedialog.h"

RenameSceneDialog::RenameSceneDialog(QWidget *parent, QString name) :
    QDialog(parent),
    _name(name),
    ui(new Ui::RenameSceneDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(name);
}

RenameSceneDialog::~RenameSceneDialog()
{
    delete ui;
}

void RenameSceneDialog::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        _name = ui->lineEdit->text();
    }
    QDialog::accept();
}

void RenameSceneDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

QString RenameSceneDialog::name()
{
    return _name;
}
