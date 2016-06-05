#ifndef INSPECTORSHADERWIDGET_H
#define INSPECTORSHADERWIDGET_H

#include <QWidget>

#include "inspectorparentwidget.h"
namespace Ui {
class InspectorShaderWidget;
}

class InspectorShaderWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorShaderWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorShaderWidget();

private:
    Ui::InspectorShaderWidget *ui;
};

#endif // INSPECTORSHADERWIDGET_H
