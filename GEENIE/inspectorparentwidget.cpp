#include "inspectorparentwidget.h"

InspectorParentWidget::InspectorParentWidget(QWidget *parent, QUuid id) :
    QWidget(parent),
    _id(id)
{

}

QUuid InspectorParentWidget::getID()
{
    return _id;
}

void InspectorParentWidget::setID(QUuid id)
{
    _id = id;
}
