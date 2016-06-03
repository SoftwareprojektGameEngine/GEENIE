#ifndef INSPECTORMATERIALWIDGET_H
#define INSPECTORMATERIALWIDGET_H

#include "inspectorparentwidget.h"

namespace Ui {
class InspectorMaterialWidget;
}

class InspectorMaterialWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorMaterialWidget(QWidget *parent = 0, QUuid id = QUuid());
    ~InspectorMaterialWidget();

private:
    Ui::InspectorMaterialWidget *ui;
};

#endif // INSPECTORMATERIALWIDGET_H
