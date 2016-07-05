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
        if(ui->checkBox->isChecked())
        {
            _component = new ModelComponent(QUuid(ui->comboBox_2->currentData(Qt::UserRole).toByteArray()),ui->lineEdit->text());
        }
        else
        {
            //TODO: Standardcomponent
        }
        break;
    }
    case ComponentType::MATERIAL:
    {
        if(ui->checkBox->isChecked())
        {
            _component = new MaterialComponent(QUuid(ui->comboBox_2->currentData(Qt::UserRole).toByteArray()),1,ui->lineEdit->text());
        }
        else
        {
            //TODO: Standardcomponent
        }
        break;
    }
    case ComponentType::POSITION:
    {
        _component = new PositionComponent(Vector(),ui->lineEdit->text());
        break;
    }
    case ComponentType::LIGHT:
    {
        Color c(0,0,0,0);
        Vector v(0,0,0,0);
        _component = new LightComponent(AMBIENT,c,c,c,v,ui->lineEdit->text());
        break;
    }
    case ComponentType::TEXTURE:
    {
        if(ui->checkBox->isChecked())
        {
            _component = new TextureComponent(QUuid(ui->comboBox_2->currentData(Qt::UserRole).toByteArray()),1,ui->lineEdit->text());
        }
        else
        {
            //TODO: Standardcomponent
        }
        break;
    }
    case ComponentType::SOUND:
    {
        if(ui->checkBox->isChecked())
        {
            _component = new SoundComponent(QUuid(ui->comboBox_2->currentData(Qt::UserRole).toByteArray()),ui->lineEdit->text());
        }
        else
        {
            //TODO: Standardcomponent
        }
        break;
    }
    case ComponentType::SHADER:
    {
        if(ui->checkBox->isChecked())
        {
            _component = new ShaderComponent(QUuid(ui->comboBox_2->currentData(Qt::UserRole).toByteArray()),ui->lineEdit->text());
        }
        else
        {
            //TODO: Standardcomponent
        }
        break;
    }
    case ComponentType::SCRIPT:
    {
        //TODO: Disable ScriptComponent?
        break;
    }
    default: QDialog::reject(); break;
    }

    QDialog::accept();
}

void AddComponentDialog::on_cancelBtn_clicked()
{
    QDialog::reject();
}

void AddComponentDialog::SetAssetList(QList<ASSET_DATA> a)
{
    if(a.size() == 0)
    {
        ui->checkBox->setChecked(false);
        ui->checkBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
    }
    QComboBox *list = ui->comboBox_2;
    for(int i=0;i<a.count();i++)
    {
        list->addItem(a.at(i).name,a.at(i).id.toByteArray());
    }
}



void AddComponentDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    if(ui->comboBox->currentIndex() == 2||
       ui->comboBox->currentIndex() == 3||
       ui->comboBox->currentIndex() == 6)
    {
        ui->checkBox->setChecked(false);
        ui->comboBox_2->setEnabled(false);
        ui->checkBox->setEnabled(false);
    }
    else
    {
        if(ui->comboBox->currentIndex()==-1)return;
        ui->checkBox->setEnabled(true);
        if(ui->checkBox->isChecked())
        {
            ui->comboBox_2->setEnabled(true);
            emit LoadAssetList(this, ui->comboBox->currentIndex());
        }
    }
}

void AddComponentDialog::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        ui->comboBox_2->setEnabled(true);
        emit LoadAssetList(this, ui->comboBox->currentIndex());
    }
    else
    {
        ui->comboBox_2->clear();
        ui->comboBox_2->setEnabled(false);
    }
}
