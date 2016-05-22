#ifndef LOGGERFILTERMODEL_H
#define LOGGERFILTERMODEL_H

#include "logger_global.h"
#include <QSortFilterProxyModel>

class LOGGERSHARED_EXPORT LoggerFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    LoggerFilterModel(QObject *parent = Q_NULLPTR);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

public slots:
    void filterChanged(bool debug, bool error, bool warning, bool info);

private:

    bool _debug;
    bool _error;
    bool _warning;
    bool _info;

};

#endif // LOGGERFILTERMODEL_H
