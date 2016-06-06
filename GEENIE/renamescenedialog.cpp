#include "renamescenedialog.h"
#include "ui_renamescenedialog.h"

RenameSceneDialog::RenameSceneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameSceneDialog)
{
    ui->setupUi(this);
}

RenameSceneDialog::~RenameSceneDialog()
{
    delete ui;
}
