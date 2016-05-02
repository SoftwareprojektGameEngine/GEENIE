#include "logger.h"
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include "loggerwidget.h"

static const QString log_file_path(QString("%1/AppData/Local/GEENIE/log/%2.log")
                                   .arg(QDir::homePath())
                                   .arg(QDate::currentDate().toString(QString("ddMMyyyy"))));

Logger& Logger::Instance()
{
    static Logger _instance;
    return _instance;
}

Logger::Logger()
{
    loggerConsole = new LoggerWidget();
}

Logger::~Logger()
{
}

void Logger::createMsg(logger::MessageType type, QString msg)
{
    loggerConsole->newMessage(msg,type);
    QFile logfile(log_file_path);
    if( logfile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append) )
    {
        QTextStream logstream(&logfile);
        switch(type)
        {
        case logger::MessageType::DEBUG:
        {
            logstream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                      << " DEBUG "
                      << msg
                      << endl;
            break;
        }
        case logger::MessageType::ERROR:
        {
            logstream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                      << " ERROR "
                      << msg
                      << endl;
            break;
        }
        case logger::MessageType::WARNING:
        {
            logstream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                      << " WARNING "
                      << msg
                      << endl;
            break;
        }
        case logger::MessageType::INFO:
        {
            logstream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                      << " INFO "
                      << msg
                      << endl;
            break;
        }
        default:
        {
            logstream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                      << " UNKNOWN "
                      << "unknown log message"
                      << endl;
        }
        }
    }
}

void Logger::createMsg(logger::MessageType type, std::string msg)
{
    createMsg(type,QString(msg.c_str()));
}

void Logger::createMsg(logger::MessageType type, const char *msg)
{
    createMsg(type,QString(msg));
}
