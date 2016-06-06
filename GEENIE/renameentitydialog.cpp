#include "renameentitydialog.h"
#include "ui_renameentitydialog.h"

RenameEntityDialog::RenameEntityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameEntityDialog)
{
    ui->setupUi(this);
}

RenameEntityDialog::~RenameEntityDialog()
{
    delete ui;
}
