#ifndef INSPECTORCAMERAWIDGET_H
#define INSPECTORCAMERAWIDGET_H

#include "inspectorparentwidget.h"

namespace Ui {
class InspectorCameraWidget;
}

class InspectorCameraWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorCameraWidget(QWidget *parent = 0, QUuid id = QUuid());
    ~InspectorCameraWidget();

private:
    Ui::InspectorCameraWidget *ui;
};

#endif // INSPECTORCAMERAWIDGET_H
