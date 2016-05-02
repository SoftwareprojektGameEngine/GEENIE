#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"
#include <string>

#define DEBUG_MSG(msg) Logger::Instance().createMsg(logger::MessageType::DEBUG,msg);
#define ERROR_MSG(msg) Logger::Instance().createMsg(logger::MessageType::ERROR,msg);
#define WARNING_MSG(msg) Logger::Instance().createMsg(logger::MessageType::WARNING,msg);
#define INFO_MSG(msg) Logger::Instance().createMsg(logger::MessageType::INFO,msg);

namespace logger {
    enum class MessageType {
        DEBUG,
        ERROR,
        WARNING,
        TEST,
        INFO
    };
}

class LOGGERSHARED_EXPORT Logger
{   
public:
    static Logger & Instance();
    Logger(Logger const&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger& operator=(Logger&&) = delete;

    void createMsg(logger::MessageType type,QString msg);
    void createMsg(logger::MessageType type, std::string msg);
    void createMsg(logger::MessageType type, const char* msg);

protected:
    Logger();
    ~Logger();
};


#endif // LOGGER_H
