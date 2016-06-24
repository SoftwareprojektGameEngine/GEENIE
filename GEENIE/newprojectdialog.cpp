#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

#include <QFileDialog>
void NewProjectDialog::on_pushButton_clicked()
{
    QString file = QFileDialog::getSaveFileName(this,"Select project file","C:/","GEENIE project file (*.geenie)");
    ui->lineEdit_2->setText(file);
}

#include <QFileInfo>
#include <QMessageBox>
void NewProjectDialog::on_pushButton_2_clicked()
{
    _name = ui->lineEdit->text();
    _file = ui->lineEdit_2->text();
    if(QFileInfo(_file).absoluteDir().entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() != 0)
    {
        QMessageBox::warning(this,QString("Not empty directory"),QString("The selected directoy is not empty.\nPlease select another directory."));
        return;
    }
    if(!_name.isEmpty() && !_file.isEmpty())
    {
        QDialog::accept();
    }
    else
    {
        QDialog::reject();
    }
}

void NewProjectDialog::on_pushButton_3_clicked()
{
    QDialog::reject();
}
