#include "geeniemainwindow.h"
#include <QApplication>
#include "geenie.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GEENIEMainWindow w;
    w.show();

    GEENIE g;

    return a.exec();
}
