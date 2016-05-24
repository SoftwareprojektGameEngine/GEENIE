#include "common.h"
#include <QDir>

Common::Common()
{

}


const QString Common::log_file_path = QString("%1/AppData/Local/GEENIE/log/%2.log")
        .arg(QDir::homePath())
        .arg(QDate::currentDate().toString(QString("ddMMyyyy")));

const QString Common::log_path = QString("%1/AppData/Local/GEENIE/log")
        .arg(QDir::homePath());

const QString Common::last_script_file_name = QString("last_script");
const QString Common::last_script_dir = QString("%1\\").arg(QDir::currentPath());

const QString Common::session_save_file_name = QString("session_save.xml");
const QString Common::session_save_dir = QString("%1\\").arg(QDir::currentPath());

const QString Common::global_stylesheet = QString("");
const QString Common::project_file_extension = QString(".geenie");
