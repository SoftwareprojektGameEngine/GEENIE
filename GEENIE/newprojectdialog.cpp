#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);

    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    this->userprofile = env.value("USERPROFILE") + "\\" + "GEENIE";

    ui->lineEdit_2->setText(userprofile);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

#include <QFileDialog>
void NewProjectDialog::on_pushButton_clicked()
{
    QString file = QFileDialog::getExistingDirectory(this,"Select the location of the project-folder",userprofile);
    ui->lineEdit_2->setText(file);
}

#include <QFileInfo>
#include <QMessageBox>
void NewProjectDialog::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text() != QString("") && ui->lineEdit->text() != QString(""))
    {
        QDir *dir = new QDir(ui->lineEdit_2->text());
        if(dir->exists())
        {
            this->_name = ui->lineEdit->text();
            this->_path = ui->lineEdit_2->text();
            QDialog::accept();
        }
        else
        {
            QMessageBox box;
            box.setWindowTitle("Error");
            box.setText("Selected Directory does not exist");
            box.setStandardButtons(QMessageBox::Ok);
            box.exec();
        }
    }
    else
    {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText("Please enter the project name and path");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
    }
}

void NewProjectDialog::on_pushButton_3_clicked()
{
    QDialog::reject();
}
