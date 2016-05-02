#include "geenie.h"
#include <QDir>

GEENIE::GEENIE(QObject *parent) : QObject(parent)
{
    QDir dir;
    dir.mkpath(Common::log_path);
}
