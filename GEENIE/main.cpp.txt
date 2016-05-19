#include "menuebar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menuebar w;
    w.show();

    return a.exec();
}
