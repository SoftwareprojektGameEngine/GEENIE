#ifndef INSPECTORTEXTUREWIDGET_H
#define INSPECTORTEXTUREWIDGET_H

#include <QWidget>
#include "inspectorparentwidget.h"

namespace Ui {
class InspectorTextureWidget;
}

class InspectorTextureWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorTextureWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorTextureWidget();

private:
    Ui::InspectorTextureWidget *ui;
};

#endif // INSPECTORTEXTUREWIDGET_H
