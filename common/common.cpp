#include "common.h"


Common::Common()
{

}


const QString Common::log_file_path = QString("%1/AppData/Local/GEENIE/log/%2.log")
        .arg(QDir::homePath())
        .arg(QDate::currentDate().toString(QString("ddMMyyyy")));

const QString Common::log_path = QString("%1/AppData/Local/GEENIE/log")
        .arg(QDir::homePath());
