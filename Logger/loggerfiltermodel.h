#ifndef LOGGERFILTERMODEL_H
#define LOGGERFILTERMODEL_H

#include "logger_global.h"
#include <QSortFilterProxyModel>

/*!
 * \brief The LoggerFilterModel class provides filtering for the error console
 */

class LOGGERSHARED_EXPORT LoggerFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    /*!
     * \brief The constructor for the LoggerFilterModel.
     * \param parent
     */
    LoggerFilterModel(QObject *parent = Q_NULLPTR);
    /*!
     * \brief Inherited from QSortFilterProxyModel to provide own options for filtering
     * \param source_row
     * \param source_parent
     * \return
     */
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

public slots:
    /*!
     * \brief Tells the model if the filter has changed.
     * \param debug
     * \param error
     * \param warning
     * \param info
     */
    void filterChanged(bool debug, bool error, bool warning, bool info);

private:

    bool _debug;
    bool _error;
    bool _warning;
    bool _info;

};

#endif // LOGGERFILTERMODEL_H
