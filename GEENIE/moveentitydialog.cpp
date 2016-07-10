#include "moveentitydialog.h"
#include "ui_moveentitydialog.h"

moveentitydialog::moveentitydialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::moveentitydialog)
{
    ui->setupUi(this);
}

moveentitydialog::~moveentitydialog()
{
    delete ui;
}



void moveentitydialog::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex()>-1)
    {
        this->newParentID = ui->comboBox->currentData(Qt::UserRole).toByteArray();
        QDialog::accept();
    }
    else
    {
        //QDialog::reject();
    }
}

void moveentitydialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

void moveentitydialog::FillComboBox(QList<ENTITY_DATA_ME> e, QUuid id)
{
    this->entityID = id;
    for(int i=0; i<e.size(); i++)
    {
        if(id !=e.at(i).entityId)
            ui->comboBox->addItem(e.at(i).entityName,e.at(i).entityId.toByteArray());
        this->FillComboBox(e.at(i).entities, id);
    }
}
