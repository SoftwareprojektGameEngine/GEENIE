#include "geenie.h"
#include "common.h"
#include "geeniemainwindow.h"

#include <QDir>
#include <QDockWidget>
#include <QLabel>
#include <QDebug>


GEENIE::GEENIE(QObject *parent) :
    QObject(parent),
    _mainWindow(new GEENIEMainWindow)
{
    createDockWidgetTitles();
    QDir dir;
    dir.mkpath(Common::log_path);

    QLabel* lbl = new QLabel();
    lbl->setText(QString("Inspector Dock"));
    QLabel* lbl2 = new QLabel();
    lbl2->setText(QString("Asset Logger Dock"));
    QLabel* lbl3 = new QLabel();
    lbl3->setText(QString("Entities Dock"));

    QLabel* lbl5 = new QLabel();
    lbl5->setText(QString("Bla"));

    insertDockWidget(EDockWidgetTypes::LoggerWidget,Logger::Instance().loggerConsole,true,Qt::LeftDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::InspectorWidget,lbl2,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::AssetsWidget,lbl3,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::EntitiesWidget,lbl5,true,Qt::BottomDockWidgetArea);

    _mainWindow->show();
}


void GEENIE::insertDockWidget(EDockWidgetTypes type, QWidget *widget, bool show, Qt::DockWidgetArea area)
{
    if(!_dockWidgets.contains(type))
    {
        QDockWidget* dWidget = new QDockWidget(_dockWidgetsTitles.value(type),_mainWindow);
        widget->setParent(dWidget);
        dWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
        dWidget->setWidget(widget);
        if(show)
        {
            if(area == Qt::LeftDockWidgetArea || area == Qt::RightDockWidgetArea || area == Qt::BottomDockWidgetArea)
            {
                _mainWindow->addDockWidget(area,dWidget);
            }
            else
            {
                _mainWindow->addDockWidget(Qt::BottomDockWidgetArea,dWidget);
            }
        }
        _dockWidgets.insert(type,dWidget);

    }
}

void GEENIE::createDockWidgetTitles()
{
    _dockWidgetsTitles.insert(EDockWidgetTypes::LoggerWidget,QString("Logger"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::InspectorWidget,QString("Inspector"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::AssetsWidget,QString("Assets"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::EntitiesWidget,QString("Entities"));
}
