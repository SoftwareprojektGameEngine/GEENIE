#include "inspectorparentwidget.h"

InspectorParentWidget::InspectorParentWidget(QWidget *parent, QUuid id, QUuid parentId, QString name) :
    QWidget(parent),
    _id(id),
    _parentId(parentId),
    _name(name)
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

QUuid InspectorParentWidget::getParentID()
{
    return _parentId;
}

void InspectorParentWidget::setParentID(QUuid id)
{
    _parentId = id;
}
