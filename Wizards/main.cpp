#include "npwizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NPWizard w;
    w.show();

    return a.exec();
}
