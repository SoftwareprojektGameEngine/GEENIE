#ifndef LOGGERLISTITEM_H
#define LOGGERLISTITEM_H

#include "logger_global.h"
#include <QString>
#include <QDateTime>

/*!
 * \brief The LoggerListItem class is an item class for the LoggerListModel. It contains the information of one Logger message.
 */

class LOGGERSHARED_EXPORT LoggerListItem
{
public:
    /*!
     * \brief Constructor
     * \param msg
     * \param timestamp
     * \param type
     */
    LoggerListItem(const QString msg = QString(), const QDateTime timestamp = QDateTime::currentDateTime(), logger::MessageType type = logger::MessageType::INFO_MSG);
    /*!
     * \brief Destructor
     */
    ~LoggerListItem(){}

    /*!
     * \brief Returns the message as full formated string.
     * \return Message
     */
    QString toString() const;
    /*!
     * \brief Returns the type of the message. (DEBUG, ERROR, WARNUNG, INFO)
     * \return
     */
    logger::MessageType type();
private:

    const QDateTime _timestamp;
    logger::MessageType _type;
    const QString _msg;
};

#endif // LOGGERLISTITEM_H
