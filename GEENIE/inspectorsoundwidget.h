#ifndef INSPECTORSOUNDWIDGET_H
#define INSPECTORSOUNDWIDGET_H

#include <QWidget>
#include "inspectorparentwidget.h"

namespace Ui {
class InspectorSoundWidget;
}

class InspectorSoundWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorSoundWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());
    ~InspectorSoundWidget();

private:
    Ui::InspectorSoundWidget *ui;
};

#endif // INSPECTORSOUNDWIDGET_H
