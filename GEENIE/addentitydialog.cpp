#include "addentitydialog.h"
#include "ui_addentitydialog.h"

AddEntityDialog::AddEntityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEntityDialog)
{
    ui->setupUi(this);
}

AddEntityDialog::~AddEntityDialog()
{
    delete ui;
}
