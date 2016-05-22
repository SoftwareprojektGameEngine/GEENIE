#include "loggerlistitem.h"

LoggerListItem::LoggerListItem(const QString msg, const QDateTime timestamp, logger::MessageType type) :
    _timestamp(timestamp),
    _type(type),
    _msg(msg)
{

}

QString LoggerListItem::toString() const
{
    switch(_type)
    {
    case logger::MessageType::DEBUG_MSG:
    {
        return QString("%1 - [DEBUG] %2").arg(_timestamp.toString("yyyy-MM-dd hh:mm:ss")).arg(_msg);
    }
    case logger::MessageType::ERROR_MSG:
    {
        return QString("%1 - [ERROR] %2").arg(_timestamp.toString("yyyy-MM-dd hh:mm:ss")).arg(_msg);
    }
    case logger::MessageType::WARNING_MSG:
    {
        return QString("%1 - [WARNING] %2").arg(_timestamp.toString("yyyy-MM-dd hh:mm:ss")).arg(_msg);
    }
    case logger::MessageType::INFO_MSG:
    {
        return QString("%1 - [INFO] %2").arg(_timestamp.toString("yyyy-MM-dd hh:mm:ss")).arg(_msg);
    }
    }
    return QString("%1 - [UNKNOWN] %2").arg(_timestamp.toString("yyyy-MM-dd hh:mm:ss")).arg(_msg);

}

logger::MessageType LoggerListItem::type()
{
    return _type;
}
