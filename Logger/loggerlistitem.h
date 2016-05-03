#ifndef LOGGERLISTITEM_H
#define LOGGERLISTITEM_H

#include "logger_global.h"
#include <QString>
#include <QDateTime>

class LOGGERSHARED_EXPORT LoggerListItem
{
public:
    LoggerListItem(const QString msg = QString(), const QDateTime timestamp = QDateTime::currentDateTime(), logger::MessageType type = logger::MessageType::INFO);
    ~LoggerListItem(){}


    QString toString() const;
    logger::MessageType type();
private:

    const QDateTime _timestamp;
    logger::MessageType _type;
    const QString _msg;
};

#endif // LOGGERLISTITEM_H
