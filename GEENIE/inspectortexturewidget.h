#ifndef INSPECTORTEXTUREWIDGET_H
#define INSPECTORTEXTUREWIDGET_H

#include "inspectorparentwidget.h"

namespace Ui {
class InspectorTextureWidget;
}

class InspectorTextureWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorTextureWidget(QWidget *parent = 0, QUuid id = QUuid());
    ~InspectorTextureWidget();

private:
    Ui::InspectorTextureWidget *ui;
};

#endif // INSPECTORTEXTUREWIDGET_H
