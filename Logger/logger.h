#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"
#include <string>
#include "loggerwidget.h"

/*!
 * \def DEBUG_MSG(msg)
 * Macro for printing debug messages
 */
#define DEBUG_MSG(msg) Logger::Instance().createMsg(logger::MessageType::DEBUG_MSG,msg);
/*!
 * \def ERROR_MSG(msg)
 * Macro for printing error messages
 */
#define ERROR_MSG(msg) Logger::Instance().createMsg(logger::MessageType::ERROR_MSG,msg);
/*!
 * \def WARNING_MSG(msg)
 * Macro for printing warning messages
 */
#define WARNING_MSG(msg) Logger::Instance().createMsg(logger::MessageType::WARNING_MSG,msg);
/*!
 * \def INFO_MSG(msg)
 * Macro for printing information messages
 */
#define INFO_MSG(msg) Logger::Instance().createMsg(logger::MessageType::INFO_MSG,msg);
/*!
 * \def LOGGER_WIDGET
 * Macro for giving simple access to the LoggerWidget
 */
#define LOGGER_WIDGET Logger::Instance().loggerConsole;


/*!
 * \class Logger logger.h
 * \brief The Logger for thread-safe logging across GEENIE
 *
 * Logger is designed with the singleton pattern, because only one instance is needed across the whole system.
 * For easier logging there are macros defined. See DEBUG_MSG, ERROR_MSG, WARNING_MSG, INFO_MSG
 *
 * \warning Only thread-safe when since C++11
 *
 * \author Artem Dontsov
 * \date 2016
 */

class LOGGERSHARED_EXPORT Logger
{   
public:
    /*!
     * \fn static Logger& Instance()
     * \brief Instance function for accessing logger
     * \return Instance of Logger
     */
    static Logger & Instance();
    /*!
     * \fn Logger(Logger const&)
     * \brief Copy constructor defined to avoid copy construction
     */
    Logger(Logger const&) = delete;
    /*!
     * \fn Logger(Logger&&)
     * \brief Copy constructor defined to avoid copy construction
     */
    Logger(Logger&&) = delete;
    /*!
     * \fn Logger& operator=(Logger const&)
     * \brief Copy constructor defined to avoid copy construction
     * \return n.a.
     */
    Logger& operator=(Logger const&) = delete;
    /*!
     * \fn Logger& operator=(Logger&&)
     * \brief Copy constructor defined to avoid copy construction
     * \return n.a.
     */
    Logger& operator=(Logger&&) = delete;

    /*!
     * \fn void createMsg(logger::MessageType type, QString msg)
     * \brief Creates a new message of type type and with message msg
     * \param type Defines type of message
     * \param msg Message
     */
    void createMsg(logger::MessageType type,QString msg);
    /*!
     * \fn void createMsg(logger::MessageType type, std::string msg)
     * \brief Reimplementation of Logger::createMsg(logger::MessageType type, QString msg) for providing std::string support
     * \param type Defines type of message
     * \param msg Message
     */
    void createMsg(logger::MessageType type, std::string msg);
    /*!
     * \fn void createMsg(logger::MessageType type, const char* msg)
     * \brief Reimplementation of Logger::createMsg(logger::MessageType type, QString msg) for providing const char* support
     * \param type Defines type of message
     * \param msg Message
     */
    void createMsg(logger::MessageType type, const char* msg);

    /*!
     * \var LoggerWidget* loggerConsole
     * \brief Provides a pointer to the logging widget
     */
    LoggerWidget* loggerConsole;

protected:
    /*!
     * \fn Logger()
     * \brief Protected constructor. See singleton design pattern
     */
    Logger();
    /*!
     * \fn ~Logger()
     * \brief Protected destructor. See singleton design pattern
     */
    ~Logger();
};


#endif // LOGGER_H
