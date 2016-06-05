#ifndef INSPECTORLIGHTWIDGET_H
#define INSPECTORLIGHTWIDGET_H

#include <QWidget>
#include <QColor>
#include "inspectorparentwidget.h"
#include "components.h"

namespace Ui {
class InspectorLightWidget;
}

class InspectorLightWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorLightWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(), Color ambient = Color(), Color diffuse = Color(), Color specular = Color(), Vector spot = Vector(), LightSourceType type = LightSourceType::AMBIENT, QString name = QString());
    ~InspectorLightWidget();

signals:
    void applyColor(Color,Color,Color,Vector,LightSourceType,QUuid,QUuid,QString);

private slots:

    void on_pushButton_clicked();

    void on_appBtn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_xSpin_valueChanged(double arg1);

    void on_ySpin_valueChanged(double arg1);

    void on_zSpin_valueChanged(double arg1);

    void on_wSpin_valueChanged(double arg1);

    void on_rSpin_valueChanged(double arg1);

    void on_gSpin_valueChanged(double arg1);

    void on_bSpin_valueChanged(double arg1);

    void on_aSpin_valueChanged(double arg1);

    void on_rSpin_2_valueChanged(double arg1);

    void on_gSpin_2_valueChanged(double arg1);

    void on_bSpin_2_valueChanged(double arg1);

    void on_aSpin_2_valueChanged(double arg1);

    void on_rSpin_3_valueChanged(double arg1);

    void on_gSpin_3_valueChanged(double arg1);

    void on_bSpin_3_valueChanged(double arg1);

    void on_aSpin_3_valueChanged(double arg1);

private:
    Color _ambientColor;
    Color _diffuseColor;
    Color _specularColor;
    Vector _spotlightDirection;
    LightSourceType _lightSourceType;
    Ui::InspectorLightWidget *ui;
    void setColor();
    void setColorFromDialog();
};

#endif // INSPECTORLIGHTWIDGET_H
