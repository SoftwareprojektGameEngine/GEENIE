#ifndef INSPECTORMODELWIDGET_H
#define INSPECTORMODELWIDGET_H

#include <QWidget>

#include "inspectorparentwidget.h"
namespace Ui {
class InspectorModelWidget;
}

class InspectorModelWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorModelWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorModelWidget();

private:
    Ui::InspectorModelWidget *ui;
};

#endif // INSPECTORMODELWIDGET_H
