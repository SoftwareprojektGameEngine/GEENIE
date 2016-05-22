#ifndef INSPECTORTRANSFORMWIDGET_H
#define INSPECTORTRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorTransformWidget;
}

class InspectorTransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorTransformWidget(QWidget *parent = 0);
    ~InspectorTransformWidget();

private:
    Ui::InspectorTransformWidget *ui;
};

#endif // INSPECTORTRANSFORMWIDGET_H
