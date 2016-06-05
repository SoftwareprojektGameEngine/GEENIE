#ifndef INSPECTORSCRIPTCOMPONENT_H
#define INSPECTORSCRIPTCOMPONENT_H

#include <QWidget>

#include "inspectorparentwidget.h"
namespace Ui {
class InspectorScriptComponent;
}

class InspectorScriptComponent : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorScriptComponent(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorScriptComponent();

private:
    Ui::InspectorScriptComponent *ui;
};

#endif // INSPECTORSCRIPTCOMPONENT_H
