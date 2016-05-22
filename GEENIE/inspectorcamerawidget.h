#ifndef INSPECTORCAMERAWIDGET_H
#define INSPECTORCAMERAWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorCameraWidget;
}

class InspectorCameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorCameraWidget(QWidget *parent = 0);
    ~InspectorCameraWidget();

private:
    Ui::InspectorCameraWidget *ui;
};

#endif // INSPECTORCAMERAWIDGET_H
