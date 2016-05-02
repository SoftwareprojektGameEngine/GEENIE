#include "geeniemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GEENIEMainWindow w;
    w.show();

    ERROR_MSG("TEST");
    DEBUG_MSG("TEST");
    WARNING_MSG("TEST");
    INFO_MSG("TEST");

    return a.exec();
}
