#include "geeniemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GEENIEMainWindow w;
    w.show();

    return a.exec();
}
