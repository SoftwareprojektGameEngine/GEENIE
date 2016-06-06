#include "addcomponentdialog.h"
#include "ui_addcomponentdialog.h"

#include "core.h"
#include "components.h"

#include <QDebug>
AddComponentDialog::AddComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponentDialog)
{
    ui->setupUi(this);
    QStringList items;
    items << "Model" << "Material" << "Position" << "Light" << "Texture" << "Sound" << "Shader" << "Script";
    ui->comboBox->addItems(items);
    ui->comboBox->setCurrentIndex(-1);
}

AddComponentDialog::~AddComponentDialog()
{
    delete ui;
}

Component* AddComponentDialog::component()
{
    return _component;
}

void AddComponentDialog::on_createBtn_clicked()
{
    switch(ui->comboBox->currentIndex())
    {
    case ComponentType::MODEL:
    {
        //_component = new ModelComponent();
    }
    case ComponentType::MATERIAL:
    {

    }
    case ComponentType::POSITION:
    {

    }
    case ComponentType::LIGHT:
    {

    }
    case ComponentType::TEXTURE:
    {

    }
    case ComponentType::SOUND:
    {

    }
    case ComponentType::SHADER:
    {

    }
    case ComponentType::SCRIPT:
    {

    }
    default: QDialog::reject(); break;
    }

    //QDialog::accept();
    QDialog::reject();
}

void AddComponentDialog::on_cancelBtn_clicked()
{
    QDialog::reject();
}
