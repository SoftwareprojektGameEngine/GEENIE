#include "exitdialog.h"
#include "ui_exitdialog.h"
#include <QMovie>

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie(QString(":/other/exit.gif"),QByteArray(),this);
    ui->label->setMovie(movie);
    movie->start();
}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::on_pushButton_clicked()
{
    this->accept();
}

void ExitDialog::on_pushButton_2_clicked()
{
    this->reject();
}
