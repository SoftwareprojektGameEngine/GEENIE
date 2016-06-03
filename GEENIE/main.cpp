#include "geeniemainwindow.h"
#include <QApplication>
#include "geenie.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL, true);

    QApplication a(argc, argv);
    /*GEENIEMainWindow w;
    w.show();*/

    GEENIE g;

    return a.exec();
}
