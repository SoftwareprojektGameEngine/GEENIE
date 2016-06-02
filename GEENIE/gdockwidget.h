#ifndef GDOCKWIDGET_H
#define GDOCKWIDGET_H

#include <QDockWidget>

class GDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    GDockWidget(const QString &title, QWidget* parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());

protected:
    void resizeEvent(QResizeEvent*event);

signals:
    void resizeSignal(int h, int w);
};

#endif // GDOCKWIDGET_H
