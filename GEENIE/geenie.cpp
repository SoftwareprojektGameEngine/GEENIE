#include "geenie.h"
#include "common.h"
#include "geeniemainwindow.h"
#include "assetwidget.h"
#include "sceneexplorer.h"
#include "../tinyxml/tinyxml.h"
#include "inspector.h"
#include "inspectoraudiowidget.h"
#include "inspectorcamerawidget.h"
#include "inspectormaterialwidget.h"
#include "inspectortexturewidget.h"
#include "inspectortransformwidget.h"
#include "inspectorwidget.h"
#include "core.h"
#include "components.h"
#include "gdockwidget.h"

#include <QDir>
#include <QFile>
#include <QDockWidget>
#include <QLabel>
#include <QDebug>
#include <QTextDocument>
#include <QStackedLayout>
#include <QTimer>
#include <QString>
#include <QScrollArea>

GEENIE::GEENIE(QObject *parent) :
    QObject(parent),
    _mainWindow(new GEENIEMainWindow),
    _layoutName("default"),
    _highlighter(new ScriptHighlighter(_mainWindow->scriptEditorDocument()))
{
    //EXAMPLE PROJECT
    _project = new Project(0,QString("untitled"));
    QUuid exEntityId;
    {
        Scene* scene = new Scene();
        _project->AddScene(scene);
        Entity* entity = new Entity(scene->GetID());
        exEntityId = entity->GetID();
        _project->AddEntity(entity);
        entity->AddComponent(new SoundComponent(QUuid::createUuid()));
        entity->AddComponent(new TextureComponent(QUuid::createUuid(),0));
        entity->AddComponent(new ModelComponent(QUuid::createUuid()));
    }
    //EXAMPLE PROJECT
    qDebug() << __LINE__;
    createDockWidgetTitles();
    QDir dir;
    dir.mkpath(Common::log_path);

    InspectorWidget* inspectorWidget = new InspectorWidget(_mainWindow);
    Inspector* inspector = new Inspector(inspectorWidget);
    _inspectorWidgets.append(inspector);
    inspectorWidget->addWidget(inspector);

qDebug() << __LINE__;
    AssetWidget* aWidget = new AssetWidget(_mainWindow);

    SceneExplorer* eWidget = new SceneExplorer(_mainWindow);
    QFile sessionSaveFile(QString("%1%2").arg(Common::session_save_dir).arg(Common::session_save_file_name));
    if(!sessionSaveFile.exists())
    {
        ERROR_MSG("Session save file does not exist");
        defaultSession(inspectorWidget,aWidget,eWidget);
    }
    else
    {
        INFO_MSG("Loading session save file.");
        TiXmlDocument doc(QString("%1%2").arg(Common::session_save_dir).arg(Common::session_save_file_name).toUtf8().data());
        bool ok = doc.LoadFile();
        if(!ok)
        {
            ERROR_MSG("Failed to load last session. Using default.");
            defaultSession(inspectorWidget,aWidget,eWidget);
        }
        else
        {
            TiXmlElement* root = doc.FirstChildElement("GEENIE");
            TiXmlElement* script = root->FirstChildElement("Script");
            TiXmlElement* scriptType = script->FirstChildElement("Type");
            if(scriptType->GetText() == "Python")
            {
                _mainWindow->setScriptType(Highlighter::Types::Python);
            }
            else
            {
                _mainWindow->setScriptType(Highlighter::Types::Lua);
            }
            TiXmlElement* scriptContent = script->FirstChildElement("Content");
            if(QString(scriptContent->Attribute("type")) == QString("file"))
            {
                QFile lastScriptFile(QString(scriptContent->GetText()));
                if(!lastScriptFile.open(QIODevice::ReadOnly))
                {
                    ERROR_MSG("Could not open last script file.");
                }
                else
                {
                    _mainWindow->setScript(QString::fromUtf8(lastScriptFile.readAll()));
                }
            }
            else
            {
                _mainWindow->setScript(QString::fromUtf8(scriptContent->GetText()));
            }
            TiXmlElement* dockables = root->FirstChildElement("Dockables");
            for(QMap<EDockWidgetTypes, QString>::Iterator it = _dockWidgetsTitles.begin(); it != _dockWidgetsTitles.end(); ++it)
            {
                TiXmlElement* dockable = dockables->FirstChildElement(it.value().toUtf8().data());
                if(!dockable)
                {
                    ERROR_MSG(QString("Dockable %1 not found.").arg(it.value()));
                    switch(it.key())
                    {
                    case EDockWidgetTypes::LoggerWidget:
                    {
                        insertDockWidget(EDockWidgetTypes::LoggerWidget,Logger::Instance().loggerConsole,true,Qt::BottomDockWidgetArea);
                        break;
                    }
                    case EDockWidgetTypes::InspectorWidget:
                    {
                        insertDockWidget(EDockWidgetTypes::InspectorWidget,inspectorWidget,true,Qt::RightDockWidgetArea);
                        break;
                    }
                    case EDockWidgetTypes::EntitiesWidget:
                    {
                        insertDockWidget(EDockWidgetTypes::EntitiesWidget,eWidget,true,Qt::LeftDockWidgetArea);
                        break;
                    }
                    case EDockWidgetTypes::AssetsWidget:
                    {
                        insertDockWidget(EDockWidgetTypes::AssetsWidget,aWidget,true,Qt::RightDockWidgetArea);
                        break;
                    }
                    case EDockWidgetTypes::ScriptEditorWidget:
                    {
                        break;
                    }
                    }
                }
                else
                {
                    INFO_MSG(QString("Dockable %1 found.").arg(it.value()));
                    bool visible = true;
                    int height = 200;
                    int width = 200;
                    bool floating = false;
                    QWidget* widget = new QWidget();
                    Qt::DockWidgetArea area = Qt::BottomDockWidgetArea;
                    EDockWidgetTypes type = it.key();
                    TiXmlElement* visibleElement = dockable->FirstChildElement("visible");
                    dockable->QueryIntAttribute("height",&height);
                    dockable->QueryIntAttribute("width",&width);
                    if(QString(visibleElement->GetText()) == QString("true"))
                    {
                        visible = true;
                    }
                    else
                    {
                        visible = false;
                    }

                    TiXmlElement* floatingElement = dockable->FirstChildElement("floating");
                    if(QString(floatingElement->GetText()) == QString("true"))
                    {
                        floating = true;
                    }
                    else
                    {
                        floating = false;
                    }
                    switch(type)
                    {
                    case EDockWidgetTypes::AssetsWidget:
                    {
                        widget = aWidget;
                        break;
                    }
                    case EDockWidgetTypes::LoggerWidget:
                    {
                        widget = Logger::Instance().loggerConsole;
                        break;
                    }
                    case EDockWidgetTypes::EntitiesWidget:
                    {
                        widget = eWidget;
                        break;
                    }
                    case EDockWidgetTypes::InspectorWidget:
                    {
                        widget = inspectorWidget;
                        break;
                    }
                    case EDockWidgetTypes::ScriptEditorWidget:
                    {
                        break;
                    }
                    }
                    TiXmlElement* dockArea = dockable->FirstChildElement("area");
                    bool ok;
                    area = (Qt::DockWidgetArea)QString(dockArea->GetText()).toInt(&ok);
                    if(!ok)
                    {
                        ERROR_MSG("Could not read area");
                        area = Qt::BottomDockWidgetArea;
                    }
                    INFO_MSG(QString("%1 has area %2.").arg(it.value()).arg(area));
                    insertDockWidget(type,widget,visible,area,floating);
                }
            }
        }
    }
    _saveTimer = new QTimer(0);
    _saveTimer->setInterval(60000);
    QObject::connect(_saveTimer,SIGNAL(timeout()),this,SLOT(saveSession()));
    _saveTimer->start();

    QObject::connect(_mainWindow,SIGNAL(saveSession()),
                     this,SLOT(saveSession()));
    QObject::connect(_mainWindow,SIGNAL(changeScriptType(Highlighter::Types)),
                     this,SLOT(changeScriptType(Highlighter::Types)));
qDebug() << __LINE__;
    EntityToInspector(_project->FindEntity(exEntityId));
    qDebug() << __LINE__;
    _mainWindow->show();
}

GEENIE::~GEENIE()
{
    _saveTimer->stop();
    delete _saveTimer;
}

void GEENIE::EntityToInspector(Entity *e)
{
    qDebug() << __LINE__;
    InspectorWidget* in = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    //QWidget* parentWidget = layout->parentWidget();
    qDebug() << __LINE__;
    for(auto widget : _inspectorWidgets)
    {
        in->removeWidget(widget);
        qDebug() << __LINE__;
        delete widget;
        //parentWidget->resize(parentWidget->width(),0);
    }
    qDebug() << __LINE__;
    InspectorTransformWidget* w = new InspectorTransformWidget(_mainWindow);
    in->addWidget(w);
    _inspectorWidgets.append(w);
    //parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
    QHashIterator<QUuid, Component*> it = e->GetComponents();
    while(it.hasNext())
    {
        it.next();
        ComponentToInspector(it.value(),true);
    }
}

void GEENIE::ComponentToInspector(Component *c, bool sub)
{
    InspectorWidget* in = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    //QWidget* parentWidget = layout->parentWidget();
    if(!sub)
    {
        for(auto widget : _inspectorWidgets)
        {
            in->removeWidget(widget);
            delete widget;
        }
    }
    switch(c->GetType())
    {
    case ComponentType::MODEL:
    {
        InspectorTransformWidget* w = new InspectorTransformWidget(_mainWindow);
        in->addWidget(w);
        _inspectorWidgets.append(w);
        //parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
        break;
    }
    case ComponentType::MATERIAL:
    {
        InspectorMaterialWidget* w = new InspectorMaterialWidget(_mainWindow);
        in->addWidget(w);
        _inspectorWidgets.append(w);
       // parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
        break;
    }
    case ComponentType::POSITION:
    {
        InspectorTransformWidget* w = new InspectorTransformWidget(_mainWindow);
        in->addWidget(w);
        _inspectorWidgets.append(w);
        //parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
        break;
    }
    case ComponentType::LIGHT:
    {

        break;
    }
    case ComponentType::TEXTURE:
    {
        InspectorTextureWidget* w = new InspectorTextureWidget(_mainWindow);
        in->addWidget(w);
        _inspectorWidgets.append(w);
        //parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
        break;
    }
    case ComponentType::SOUND:
    {
        InspectorAudioWidget* w = new InspectorAudioWidget(_mainWindow);
        in->addWidget(w);
        _inspectorWidgets.append(w);
        //parentWidget->resize(parentWidget->width(),parentWidget->height() + w->height());
        break;
    }
    case ComponentType::SHADER:
    {
        break;
    }
    case ComponentType::SCRIPT:
    {
        break;
    }
    }
}

void GEENIE::UnsetInspector()
{
    InspectorWidget* w = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    for(auto widget : _inspectorWidgets)
    {
        w->removeWidget(widget);
        delete widget;
    }
    Inspector* i = new Inspector(w->parentWidget());
    w->addWidget(i);
    _inspectorWidgets.append(i);

}

void GEENIE::defaultSession(QWidget *inspector, QWidget *asset, QWidget *entities)
{
    insertDockWidget(EDockWidgetTypes::LoggerWidget,Logger::Instance().loggerConsole,true,Qt::BottomDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::InspectorWidget,inspector,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::AssetsWidget,asset,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::EntitiesWidget,entities,true,Qt::LeftDockWidgetArea);
}

void GEENIE::insertDockWidget(EDockWidgetTypes type, QWidget *widget, bool show, Qt::DockWidgetArea area, bool floating, int width, int height)
{
    if(!_dockWidgets.contains(type))
    {
        GDockWidget* dWidget = new GDockWidget(_dockWidgetsTitles.value(type),_mainWindow);
        widget->setParent(dWidget);
        dWidget->setGeometry(0,0,width,height);
        dWidget->setMinimumHeight(200);
        dWidget->setMinimumWidth(200);
        dWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
        dWidget->setWidget(widget);
        dWidget->layout()->setContentsMargins(0,0,0,0);
        if(type == EDockWidgetTypes::InspectorWidget)
        {
            QObject::connect(dWidget,SIGNAL(resizeSignal(int,int)),dynamic_cast<InspectorWidget*>(widget),SLOT(resizeSlot(int,int)));
        }

        if(area == Qt::LeftDockWidgetArea || area == Qt::RightDockWidgetArea || area == Qt::BottomDockWidgetArea)
        {
            _mainWindow->addDockWidget(area,dWidget);
        }
        else
        {
            _mainWindow->addDockWidget(Qt::BottomDockWidgetArea,dWidget);
        }
        dWidget->setFloating(floating);

        if(show)
        {
            dWidget->show();
        }
        else
        {
            dWidget->hide();
        }
        _dockWidgets.insert(type,dWidget);

    }
    else
    {
        ERROR_MSG(QString("MainWindow already contains type."));
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
    INFO_MSG("Saving current session.");
    QFile sessionSaveFile(QString("%1%2").arg(Common::session_save_dir).arg(Common::session_save_file_name));
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
    TiXmlElement* scriptContent = new TiXmlElement("Content");
    if(_highlighter->document()->lineCount() > 3)
    {
        scriptContent->SetAttribute("type","file");
        QString fileExt;
        if(_highlighter->currentType() == Highlighter::Types::Python)
        {
            fileExt = QString(".py");
        }
        else
        {
            fileExt = QString(".lua");
        }
        QFile script(QString("%1\\%2%3").arg(Common::last_script_dir).arg(Common::last_script_file_name).arg(fileExt));
        script.open(QIODevice::WriteOnly);
        QTextStream ts(&script);
        ts << _highlighter->document()->toPlainText();
        script.close();
        scriptContent->LinkEndChild(new TiXmlText(QString("%1\\%2%3").arg(Common::last_script_dir).arg(Common::last_script_file_name).arg(fileExt).toUtf8().data()));
    }
    else
    {
        scriptContent->SetAttribute("type","inline");
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

        dockable->SetAttribute("width",dynamic_cast<QDockWidget*>(it.value())->geometry().width());
        dockable->SetAttribute("height",dynamic_cast<QDockWidget*>(it.value())->geometry().height());

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
    doc.SaveFile(QString("%1%2").arg(Common::session_save_dir).arg(Common::session_save_file_name).toUtf8().data());

}

void GEENIE::changeScriptType(Highlighter::Types type)
{
    _highlighter->changeType(type);
}
