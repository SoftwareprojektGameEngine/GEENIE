#ifndef INSPECTORTRANSFORMWIDGET_H
#define INSPECTORTRANSFORMWIDGET_H

#include "inspectorparentwidget.h"

namespace Ui {
class InspectorTransformWidget;
}

class InspectorTransformWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorTransformWidget(QWidget *parent = 0, QUuid id = QUuid());
    ~InspectorTransformWidget();

private:
    Ui::InspectorTransformWidget *ui;
};

#endif // INSPECTORTRANSFORMWIDGET_H
