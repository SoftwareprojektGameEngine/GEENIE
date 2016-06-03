#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorWidget;
}

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = 0);
    ~InspectorWidget();

    void addWidget(QWidget* widget);
    void removeWidget(QWidget* widget);

public slots:
    void resizeSlot(int h, int w);

private:
    Ui::InspectorWidget *ui;
};

#endif // INSPECTORWIDGET_H
