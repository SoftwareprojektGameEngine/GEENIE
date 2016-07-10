#include "geeniemainwindow.h"
#include <QApplication>
#include "geenie.h"
#include <QTextStream>
#include <QFile>

//Vorläufige Methode zum laden von designdateien. Damit Robert rumprobieren kann
void UseStyleSheets(){
    QFile file( "Stylesheets.qss" );

    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ){
        /*QMessageBox msg;
        msg.setText("Failed to load Stylesheet-File!");
        msg.exec();*/
    }
    QTextStream textstream( &file );
    QString style = textstream.readAll();
    //qApp->setStyleSheet( style );
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL, true);

    QApplication a(argc, argv);
    /*GEENIEMainWindow w;
    w.show();*/
    UseStyleSheets();

    GEENIE g;

    return a.exec();
}
