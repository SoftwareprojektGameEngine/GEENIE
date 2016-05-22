#ifndef INSPECTORMATERIALWIDGET_H
#define INSPECTORMATERIALWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorMaterialWidget;
}

class InspectorMaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorMaterialWidget(QWidget *parent = 0);
    ~InspectorMaterialWidget();

private:
    Ui::InspectorMaterialWidget *ui;
};

#endif // INSPECTORMATERIALWIDGET_H
