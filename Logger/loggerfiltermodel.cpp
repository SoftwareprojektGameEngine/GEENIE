#include "loggerfiltermodel.h"
#include "loggerlistitem.h"
#include "loggerlistmodel.h"
#include "logger.h"

#include <QDebug>

LoggerFilterModel::LoggerFilterModel(QObject* parent) :
    QSortFilterProxyModel(parent),
    _debug(true),
    _error(true),
    _warning(true),
    _info(true)
{
    setDynamicSortFilter(true);
}

void LoggerFilterModel::filterChanged(bool debug, bool error, bool warning, bool info)
{
    _debug = debug;
    _error = error;
    _warning = warning;
    _info = info;
    invalidateFilter();
}

bool LoggerFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    qDebug() << __LINE__;
    if(this->sourceModel() != nullptr)
    {
        QModelIndex index = sourceModel()->index(source_row,0,source_parent);
        if(index.isValid())
        {
            LoggerListItem* item = dynamic_cast<LoggerListModel*>(sourceModel())->itemAt(source_row);
            if(_debug && (item->type() == logger::MessageType::DEBUG))
            {
                return true;
            }
            if(_error && (item->type() == logger::MessageType::ERROR))
            {
                return true;
            }
            if(_warning && (item->type() == logger::MessageType::WARNING))
            {
                return true;
            }
            if(_info && (item->type() == logger::MessageType::INFO))
            {
                return true;
            }
        }
    }
    return false;
}
