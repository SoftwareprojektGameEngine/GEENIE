#include "gdockwidget.h"

GDockWidget::GDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags) :
    QDockWidget(title,parent,flags)
{

}

void GDockWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    emit resizeSignal(this->height() - 22,this->width()-3);
}
