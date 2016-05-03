#ifndef LOGGERLISTMODEL_H
#define LOGGERLISTMODEL_H

#include "logger_global.h"
#include <QAbstractListModel>
#include <QVector>

class LoggerListItem;


class LOGGERSHARED_EXPORT LoggerListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LoggerListModel(QObject* parent = Q_NULLPTR);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    bool insertRows(int row, int count, const QModelIndex &, LoggerListItem* item);
    bool removeRows(int row, int count, const QModelIndex &parent);

    void append(LoggerListItem* item);
    LoggerListItem* itemAt(int row) const;

private:
    QObject* _parent;

    mutable QVector<LoggerListItem*> _items;
};

#endif // LOGGERLISTMODEL_H
