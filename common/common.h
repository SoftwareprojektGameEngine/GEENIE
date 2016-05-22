#ifndef COMMON_H
#define COMMON_H

#include "common_global.h"
#include <QString>
#include <QDir>
#include <QDateTime>

class COMMONSHARED_EXPORT Common
{

public:
    Common();
    static const QString log_file_path;
    static const QString log_path;
};

#endif // COMMON_H
