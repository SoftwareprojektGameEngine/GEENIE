#include "inspectorlightwidget.h"
#include "ui_inspectorlightwidget.h"

InspectorLightWidget::InspectorLightWidget(QWidget *parent, QUuid id, QUuid parentId, Color ambient, Color diffuse, Color specular, Vector spot, LightSourceType type, QString name) :
    InspectorParentWidget(parent,id,parentId,name),
    _ambientColor(ambient),
    _diffuseColor(diffuse),
    _specularColor(specular),
    _spotlightDirection(spot),
    _lightSourceType(type),
    ui(new Ui::InspectorLightWidget)
{
    ui->setupUi(this);
    QStringList list;
    list << "Ambient" << "Diffuse" << "Spot" << "Specular";
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentIndex((int)_lightSourceType);
    ui->xSpin->setValue(_spotlightDirection.x);
    ui->ySpin->setValue(_spotlightDirection.y);
    ui->zSpin->setValue(_spotlightDirection.z);
    ui->wSpin->setValue(_spotlightDirection.w);
    setColorFromDialog();
    ui->lineEdit->setText(_name);
}

InspectorLightWidget::~InspectorLightWidget()
{
    delete ui;
}

void InspectorLightWidget::setColor()
{
    QPixmap p(30,30);
    p.fill(QColor::fromRgbF(_ambientColor.r,_ambientColor.g,_ambientColor.b,_ambientColor.a));
    ui->pushButton->setIcon(QIcon(p));
    p.fill(QColor::fromRgbF(_diffuseColor.r,_diffuseColor.g,_diffuseColor.b,_diffuseColor.a));
    ui->pushButton_2->setIcon(QIcon(p));
    p.fill(QColor::fromRgbF(_specularColor.r,_specularColor.g,_specularColor.b,_specularColor.a));
    ui->pushButton_3->setIcon(QIcon(p));
}

void InspectorLightWidget::setColorFromDialog()
{
    setColor();
    ui->rSpin->setValue(_ambientColor.r);
    ui->rSpin_2->setValue(_diffuseColor.r);
    ui->rSpin_3->setValue(_specularColor.r);
    ui->gSpin->setValue(_ambientColor.g);
    ui->gSpin_2->setValue(_diffuseColor.g);
    ui->gSpin_3->setValue(_specularColor.g);
    ui->bSpin->setValue(_ambientColor.b);
    ui->bSpin_2->setValue(_diffuseColor.b);
    ui->bSpin_3->setValue(_specularColor.b);
    ui->aSpin->setValue(_ambientColor.a);
    ui->aSpin_2->setValue(_diffuseColor.a);
    ui->aSpin_3->setValue(_specularColor.a);
}

#include <QColorDialog>

void InspectorLightWidget::on_pushButton_clicked()
{
    QColorDialog cd(QColor::fromRgbF(_ambientColor.r,_ambientColor.g,_ambientColor.b,_ambientColor.a),this);
    if(cd.exec() == QDialog::Accepted)
    {
        _ambientColor = Color(cd.selectedColor().redF(),cd.selectedColor().greenF(),cd.selectedColor().blueF(),cd.selectedColor().alphaF());
        setColorFromDialog();
    }

}

void InspectorLightWidget::on_appBtn_clicked()
{
    emit applyColor(_ambientColor,_diffuseColor,_specularColor,_spotlightDirection,_lightSourceType,_id,_parentId,ui->lineEdit->text());
}

void InspectorLightWidget::on_pushButton_2_clicked()
{
    QColorDialog cd(QColor::fromRgbF(_diffuseColor.r,_diffuseColor.g,_diffuseColor.b,_diffuseColor.a),this);
    if(cd.exec() == QDialog::Accepted)
    {
        _diffuseColor = Color(cd.selectedColor().redF(),cd.selectedColor().greenF(),cd.selectedColor().blueF(),cd.selectedColor().alphaF());
        setColorFromDialog();
    }
}

void InspectorLightWidget::on_pushButton_3_clicked()
{
    QColorDialog cd(QColor::fromRgbF(_specularColor.r,_specularColor.g,_specularColor.b,_specularColor.a),this);
    if(cd.exec() == QDialog::Accepted)
    {
        _specularColor = Color(cd.selectedColor().redF(),cd.selectedColor().greenF(),cd.selectedColor().blueF(),cd.selectedColor().alphaF());
        setColorFromDialog();
    }
}

void InspectorLightWidget::on_xSpin_valueChanged(double arg1)
{
    _spotlightDirection.x = arg1;
}

void InspectorLightWidget::on_ySpin_valueChanged(double arg1)
{
    _spotlightDirection.y = arg1;
}

void InspectorLightWidget::on_zSpin_valueChanged(double arg1)
{
    _spotlightDirection.z = arg1;
}

void InspectorLightWidget::on_wSpin_valueChanged(double arg1)
{
    _spotlightDirection.w = arg1;
}

void InspectorLightWidget::on_rSpin_valueChanged(double arg1)
{
    _ambientColor.r = arg1;
    setColor();
}

void InspectorLightWidget::on_gSpin_valueChanged(double arg1)
{
    _ambientColor.g = arg1;
    setColor();
}

void InspectorLightWidget::on_bSpin_valueChanged(double arg1)
{
    _ambientColor.b = arg1;
    setColor();
}

void InspectorLightWidget::on_aSpin_valueChanged(double arg1)
{
    _ambientColor.a = arg1;
    setColor();
}

void InspectorLightWidget::on_rSpin_2_valueChanged(double arg1)
{
    _diffuseColor.r = arg1;
    setColor();
}

void InspectorLightWidget::on_gSpin_2_valueChanged(double arg1)
{
    _diffuseColor.g = arg1;
    setColor();
}

void InspectorLightWidget::on_bSpin_2_valueChanged(double arg1)
{
    _diffuseColor.b = arg1;
    setColor();
}

void InspectorLightWidget::on_aSpin_2_valueChanged(double arg1)
{
    _diffuseColor.a = arg1;
    setColor();
}

void InspectorLightWidget::on_rSpin_3_valueChanged(double arg1)
{
    _specularColor.r = arg1;
    setColor();
}

void InspectorLightWidget::on_gSpin_3_valueChanged(double arg1)
{
    _specularColor.g = arg1;
    setColor();
}

void InspectorLightWidget::on_bSpin_3_valueChanged(double arg1)
{
    _specularColor.b = arg1;
    setColor();
}

void InspectorLightWidget::on_aSpin_3_valueChanged(double arg1)
{
    _specularColor.a = arg1;
    setColor();
}
