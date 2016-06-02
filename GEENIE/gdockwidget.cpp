#include "gdockwidget.h"

GDockWidget::GDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags) :
    QDockWidget(title,parent,flags)
{

}

#include <QResizeEvent>
#include <QDebug>
void GDockWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    //QDockWidget::resizeEvent(event);
    emit resizeSignal(this->height() - 22,this->width()-3);
}
