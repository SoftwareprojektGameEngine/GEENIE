#include "scriptwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScriptWindow w;
    w.show();

    return a.exec();
}
