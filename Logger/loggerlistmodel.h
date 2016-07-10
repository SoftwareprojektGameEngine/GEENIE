#ifndef LOGGERLISTMODEL_H
#define LOGGERLISTMODEL_H

#include "logger_global.h"
#include <QAbstractListModel>
#include <QVector>

class LoggerListItem;

/*!
 * \brief The LoggerListModel class provides a model for the LoggerWidget for displaying message data.
 */

class LOGGERSHARED_EXPORT LoggerListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param parent
     */
    LoggerListModel(QObject* parent = Q_NULLPTR);
    /*!
     * \brief Reimplementation of QAbstractItemModel::data()
     * \param index
     * \param role
     * \return Data depending of index and role
     */
    QVariant data(const QModelIndex &index, int role) const;
    /*!
     * \brief Reimplementation of QAbstractItemModel::rowCount()
     * \param parent
     * \return Number of visible messages
     */
    int rowCount(const QModelIndex &parent) const;
    /*!
     * \brief Reimplementation of QAbstractItemModel::insertRows()
     * \param row
     * \param count
     * \param parent
     * \param item
     * \return Whether the rows are successfully inserted or not
     */
    bool insertRows(int row, int count, const QModelIndex &parent, LoggerListItem* item);
    /*!
     * \brief Reimplementation of QAbstractItemModel::removeRows()
     * \param row
     * \param count
     * \param parent
     * \return Whether the rows are successfully removed or not
     */
    bool removeRows(int row, int count, const QModelIndex &parent);

    /*!
     * \brief Appends a new message to the list
     * \param item
     */
    void append(LoggerListItem* item);
    /*!
     * \brief itemAt
     * \param row
     * \return Returns the item at row
     */
    LoggerListItem* itemAt(int row) const;

private:
    QObject* _parent;

    mutable QVector<LoggerListItem*> _items;
};

#endif // LOGGERLISTMODEL_H
