#include "assetwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AssetWindow w;
    w.show();

    return a.exec();
}
