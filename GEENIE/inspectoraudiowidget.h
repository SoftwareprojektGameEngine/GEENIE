#ifndef INSPECTORAUDIOWIDGET_H
#define INSPECTORAUDIOWIDGET_H

#include "inspectorparentwidget.h"

namespace Ui {
class InspectorAudioWidget;
}

class InspectorAudioWidget : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit InspectorAudioWidget(QWidget *parent = 0, QUuid id = QUuid());
    ~InspectorAudioWidget();

private:
    Ui::InspectorAudioWidget *ui;
};

#endif // INSPECTORAUDIOWIDGET_H
