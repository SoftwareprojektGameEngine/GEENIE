#include "loggerlistmodel.h"
#include "loggerlistitem.h"
#include <QBrush>
#include <QDebug>

LoggerListModel::LoggerListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant LoggerListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    if(index.row() >= _items.size())
    {
        return QVariant();
    }
    logger::MessageType type = _items.at(index.row())->type();
    if(role == Qt::DisplayRole)
    {
        return _items.at(index.row())->toString();
    }
    else if(role == Qt::ForegroundRole)
    {
        switch(type)
        {
        case logger::MessageType::DEBUG_MSG:
            return QBrush(QColor(69,154,6));
        case logger::MessageType::ERROR_MSG:
            return QBrush(QColor(204,0,0));
        case logger::MessageType::WARNING_MSG:
            return QBrush(QColor(170,160,0));
        case logger::MessageType::INFO_MSG:
            return QBrush(QColor(255,255,255));
        default:
            return QBrush(QColor(255,255,255));
        }
    }
    return QVariant();
}

int LoggerListModel::rowCount(const QModelIndex&) const
{
    return _items.size();
}

void LoggerListModel::append(LoggerListItem *item)
{
    if(_items.size() == 500)
    {
        removeRows(0,0,QModelIndex());
    }
    insertRows(_items.size(), 1, QModelIndex(),item);
}

bool LoggerListModel::insertRows(int row, int count, const QModelIndex& parent, LoggerListItem *item)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(),row,row+count-1);
    _items.push_back(item);
    endInsertRows();

    return true;
}

bool LoggerListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(row);
    Q_UNUSED(count);

    beginRemoveRows(QModelIndex(),0,0);
    _items.pop_front();
    endRemoveRows();

    return true;
}

LoggerListItem* LoggerListModel::itemAt(int row) const
{
    return _items.at(row);
}
