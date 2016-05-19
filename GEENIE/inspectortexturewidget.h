#ifndef INSPECTORTEXTUREWIDGET_H
#define INSPECTORTEXTUREWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorTextureWidget;
}

class InspectorTextureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorTextureWidget(QWidget *parent = 0);
    ~InspectorTextureWidget();

private:
    Ui::InspectorTextureWidget *ui;
};

#endif // INSPECTORTEXTUREWIDGET_H
