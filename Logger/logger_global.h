#ifndef LOGGER_GLOBAL_H
#define LOGGER_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include "common.h"

#if defined(LOGGER_LIBRARY)
#  define LOGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LOGGERSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace logger {
    enum class MessageType {
        DEBUG_MSG,
        ERROR_MSG,
        WARNING_MSG,
        INFO_MSG
    };
}

#endif // LOGGER_GLOBAL_H
