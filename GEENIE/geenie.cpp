#include "geenie.h"
#include "common.h"
#include "geeniemainwindow.h"
#include "assetwidget.h"

#include "../tinyxml/tinyxml.h"

#include <QDir>
#include <QFile>
#include <QDockWidget>
#include <QLabel>
#include <QDebug>
#include <QTextDocument>

GEENIE::GEENIE(QObject *parent) :
    QObject(parent),
    _mainWindow(new GEENIEMainWindow),
    _layoutName("default"),
    _highlighter(new ScriptHighlighter(_mainWindow->scriptEditorDocument()))
{
    createDockWidgetTitles();
    QDir dir;
    dir.mkpath(Common::log_path);

    QLabel* lbl = new QLabel();
    lbl->setText(QString("Inspector Dock"));
    QLabel* lbl2 = new QLabel();
    lbl2->setText(QString("Asset Logger Dock"));
    AssetWidget* aWidget = new AssetWidget(_mainWindow);

    QLabel* lbl5 = new QLabel();
    lbl5->setText(QString("Bla"));

    insertDockWidget(EDockWidgetTypes::LoggerWidget,Logger::Instance().loggerConsole,true,Qt::LeftDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::InspectorWidget,lbl2,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::AssetsWidget,aWidget,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::EntitiesWidget,lbl5,true,Qt::BottomDockWidgetArea);

    QObject::connect(_mainWindow,SIGNAL(saveSession()),
                     this,SLOT(saveSession()));
    QObject::connect(_mainWindow,SIGNAL(changeScriptType(Highlighter::Types)),
                     this,SLOT(changeScriptType(Highlighter::Types)));
    _mainWindow->show();
}


void GEENIE::insertDockWidget(EDockWidgetTypes type, QWidget *widget, bool show, Qt::DockWidgetArea area)
{
    if(!_dockWidgets.contains(type))
    {
        QDockWidget* dWidget = new QDockWidget(_dockWidgetsTitles.value(type),_mainWindow);
        widget->setParent(dWidget);
        dWidget->setMinimumHeight(200);
        dWidget->setMinimumWidth(200);
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

void GEENIE::saveSession()
{
    QFile sessionSaveFile(QString("%1\\session_save.xml").arg(QDir::currentPath()));
    if(!sessionSaveFile.exists())
    {
        sessionSaveFile.open(QIODevice::WriteOnly);
        sessionSaveFile.close();
    }

    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","","");
    doc.LinkEndChild(decl);
    TiXmlElement* root = new TiXmlElement("GEENIE");
    doc.LinkEndChild(root);
    TiXmlElement* script = new TiXmlElement("Script");
    TiXmlElement* scriptContent;
    if(_highlighter->document()->lineCount() > 3)
    {
        QString fileExt;
        if(_highlighter->currentType() == Highlighter::Types::Python)
        {
            fileExt = QString(".py");
        }
        else
        {
            fileExt = QString(".lua");
        }
        scriptContent = new TiXmlElement("ContentFile");
        QFile script(QString("%1\\last_script%2").arg(QDir::currentPath()).arg(fileExt));
        script.open(QIODevice::WriteOnly);
        QTextStream ts(&script);
        ts << _highlighter->document()->toPlainText();
        script.close();
    }
    else
    {
        scriptContent = new TiXmlElement("Content");
        scriptContent->LinkEndChild(new TiXmlText(_highlighter->document()->toPlainText().toUtf8().data()));
    }
    TiXmlElement* scriptType = new TiXmlElement("Type");
    if(_highlighter->currentType() == Highlighter::Types::Python)
    {
        scriptType->LinkEndChild(new TiXmlText("Python"));
    }
    else
    {
        scriptType->LinkEndChild(new TiXmlText("Lua"));
    }
    script->LinkEndChild(scriptContent);
    script->LinkEndChild(scriptType);
    root->LinkEndChild(script);
    TiXmlElement* dockables = new TiXmlElement("Dockables");
    root->LinkEndChild(dockables);

    for(QMap<EDockWidgetTypes, QDockWidget*>::Iterator it = _dockWidgets.begin(); it != _dockWidgets.end(); ++it)
    {
        TiXmlElement* dockable = new TiXmlElement(_dockWidgetsTitles.value(it.key()).toUtf8().data());
        dockables->LinkEndChild(dockable);

        TiXmlElement* visible = new TiXmlElement("visible");
        if(dynamic_cast<QDockWidget*>(it.value())->isVisible())
        {
            visible->LinkEndChild(new TiXmlText("true"));
        }
        else
        {
            visible->LinkEndChild(new TiXmlText("false"));
        }
        dockable->LinkEndChild(visible);

        TiXmlElement* floating = new TiXmlElement("floating");
        if(dynamic_cast<QDockWidget*>(it.value())->isFloating())
        {
            floating->LinkEndChild(new TiXmlText("true"));
        }
        else
        {
            floating->LinkEndChild(new TiXmlText("false"));
        }
        dockable->LinkEndChild(floating);
        TiXmlElement* dockArea = new TiXmlElement("area");
        dockArea->LinkEndChild(new TiXmlText(QString::number(_mainWindow->dockWidgetArea(dynamic_cast<QDockWidget*>(it.value()))).toUtf8().data()));
        dockable->LinkEndChild(dockArea);
    }
    doc.SaveFile("session_save.xml");

}

void GEENIE::changeScriptType(Highlighter::Types type)
{
    _highlighter->changeType(type);
}
