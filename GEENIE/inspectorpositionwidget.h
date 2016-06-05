#ifndef INSPECTORPOSITIONWIDGET_H
#define INSPECTORPOSITIONWIDGET_H

#include <QWidget>
#include "components.h"
#include "inspectorparentwidget.h"

namespace Ui {
class InspectorPositionWidget;
}

class InspectorPositionWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorPositionWidget(QWidget *parent = 0,Vector vector = Vector(), QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorPositionWidget();

signals:
    void applyPosition(Vector,QUuid,QUuid,QString);

private slots:
    void on_xSpin_valueChanged(double arg1);

    void on_ySpin_valueChanged(double arg1);

    void on_zSpin_valueChanged(double arg1);

    void on_wSpin_valueChanged(double arg1);

    void on_appBtn_clicked();

private:
    Vector _vector;
    Ui::InspectorPositionWidget *ui;
};

#endif // INSPECTORPOSITIONWIDGET_H
