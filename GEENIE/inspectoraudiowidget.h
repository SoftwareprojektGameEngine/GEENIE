#ifndef INSPECTORAUDIOWIDGET_H
#define INSPECTORAUDIOWIDGET_H

#include <QWidget>

namespace Ui {
class InspectorAudioWidget;
}

class InspectorAudioWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorAudioWidget(QWidget *parent = 0);
    ~InspectorAudioWidget();

private:
    Ui::InspectorAudioWidget *ui;
};

#endif // INSPECTORAUDIOWIDGET_H
