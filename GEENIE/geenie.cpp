#include "geenie.h"
#include "common.h"
#include "geeniemainwindow.h"
#include "assetwidget.h"
#include "sceneexplorer.h"
#include "../tinyxml/tinyxml.h"
#include "inspector.h"
#include "inspectorlightwidget.h"
#include "inspectormaterialwidget.h"
#include "inspectormodelwidget.h"
#include "inspectorpositionwidget.h"
#include "inspectorscriptcomponent.h"
#include "inspectorshaderwidget.h"
#include "inspectorsoundwidget.h"
#include "inspectortexturewidget.h"
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
        entity->AddComponent(new SoundComponent(QUuid::createUuid(), QString("Sound 1")));
        entity->AddComponent(new TextureComponent(QUuid::createUuid(),0,QUuid::createUuid(),QString("Texture 1")));
        entity->AddComponent(new ModelComponent(QUuid::createUuid(),QUuid::createUuid(),QString("Model 1")));
        entity->AddComponent(new LightComponent(LightSourceType::AMBIENT,
                                                Color(0,0,0,0),
                                                Color(0,0,0,0),
                                                Color(0,0,0,0),
                                                Vector(),
                                                QUuid::createUuid(),
                                                QString("Light 1")));
    }
    //EXAMPLE PROJECT
    createDockWidgetTitles();
    QDir dir;
    dir.mkpath(Common::log_path);

    InspectorWidget* inspectorWidget = new InspectorWidget(_mainWindow);
    Inspector* inspector = new Inspector(inspectorWidget);
    _inspectorWidgets.append(inspector);
    inspectorWidget->addWidget(inspector);

    AssetWidget* aWidget = new AssetWidget(_mainWindow);

    SceneExplorer* eWidget = new SceneExplorer(_mainWindow);

    eWidget->setHeader(_project->name());


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
                    int x = 0;
                    int y = 0;
                    bool floating = false;
                    QWidget* widget = new QWidget();
                    Qt::DockWidgetArea area = Qt::BottomDockWidgetArea;
                    EDockWidgetTypes type = it.key();
                    TiXmlElement* visibleElement = dockable->FirstChildElement("visible");
                    dockable->QueryIntAttribute("height",&height);
                    dockable->QueryIntAttribute("width",&width);
                    dockable->QueryIntAttribute("x",&x);
                    dockable->QueryIntAttribute("y",&y);
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
                    insertDockWidget(type,widget,visible,area,floating,width,height,x,y);
                }
            }
        }
    }
    _saveTimer = new QTimer(0);
    _saveTimer->setInterval(300000);
    QObject::connect(_saveTimer,SIGNAL(timeout()),this,SLOT(saveSession()));
    _saveTimer->start();

    QObject::connect(_mainWindow,SIGNAL(saveSession()),
                     this,SLOT(saveSession()));
    QObject::connect(_mainWindow,SIGNAL(changeScriptType(Highlighter::Types)),
                     this,SLOT(changeScriptType(Highlighter::Types)));
    QObject::connect(_mainWindow,SIGNAL(toggleDock(EDockWidgetTypes,bool)),
                     this,SLOT(toggleDock(EDockWidgetTypes,bool)));
    QObject::connect(eWidget,SIGNAL(clicked(QUuid,se::ItemType)),this,SLOT(ExplorerClicked(QUuid,se::ItemType)));
    QObject::connect(eWidget,SIGNAL(clicked(QUuid,se::ItemType,QUuid)),this,SLOT(ExplorerClicked(QUuid,se::ItemType,QUuid)));
    QObject::connect(eWidget,SIGNAL(sceneClicked()),this,SLOT(UnsetInspector()));

    UnsetInspector();
    fillSceneExplorer();
    _mainWindow->show();
}

GEENIE::~GEENIE()
{
    _saveTimer->stop();
    delete _saveTimer;
}

void GEENIE::toggleDock(EDockWidgetTypes type, bool show)
{
    if(show)
    {
        _dockWidgets.value(type)->show();
    }
    else
    {
        _dockWidgets.value(type)->hide();
    }
}

void GEENIE::ExplorerClicked(QUuid id, se::ItemType)
{
    EntityToInspector(_project->FindEntity(id));
}

void GEENIE::ExplorerClicked(QUuid id, se::ItemType, QUuid parentId)
{
    ComponentToInspector(_project->FindEntity(parentId)->GetComponent(id),parentId);
}

void GEENIE::fillSceneExplorer()
{
    SceneExplorer *s = dynamic_cast<SceneExplorer*>(_dockWidgets.value(EDockWidgetTypes::EntitiesWidget)->widget());
    s->clear();
    QHashIterator<QUuid, Scene*> it = _project->GetScenes();
    while(it.hasNext())
    {
        it.next();
        SCENEID id = s->AddScene(it.value()->name(),it.key());
        QHashIterator<QUuid, Entity*> eit = it.value()->GetEntities();
        while(eit.hasNext())
        {
            eit.next();
            fillSceneExplorerWithEntities(id,eit.value());
        }
    }
}

void GEENIE::fillSceneExplorerWithEntities(SCENEID sceneId, Entity *e)
{
    SceneExplorer *s = dynamic_cast<SceneExplorer*>(_dockWidgets.value(EDockWidgetTypes::EntitiesWidget)->widget());
    ENTITYID id = s->AddEntity(e->name(),sceneId,e->GetID());
    QHashIterator<QUuid, Entity*> it = e->GetSubEntities();
    while(it.hasNext())
    {
        it.next();
        fillSceneExplorerWithEntities(sceneId, it.value());
    }
    QHashIterator<QUuid, Component*> cit = e->GetComponents();
    while(cit.hasNext())
    {
        cit.next();
        s->AddComponent(cit.value()->name(),sceneId,id,cit.value()->GetID(),e->GetID());
    }
}

void GEENIE::EntityToInspector(Entity *e)
{
    InspectorWidget* in = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    for(auto widget : _inspectorWidgets)
    {
        in->removeWidget(widget);
        delete widget;
    }
    _inspectorWidgets.clear();
    QHashIterator<QUuid, Component*> it = e->GetComponents();
    while(it.hasNext())
    {
        it.next();
        ComponentToInspector(it.value(),e->GetID(),true);
    }
}

void GEENIE::ComponentToInspector(Component *c, QUuid parent, bool sub)
{
    InspectorWidget* in = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    if(!sub)
    {
        for(auto widget : _inspectorWidgets)
        {
            in->removeWidget(widget);
            delete widget;
        }
        _inspectorWidgets.clear();
    }
    switch(c->GetType())
    {
    case ComponentType::MODEL:
    {
        InspectorModelWidget* w = new InspectorModelWidget(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::MATERIAL:
    {
        InspectorMaterialWidget* w = new InspectorMaterialWidget(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::POSITION:
    {
        PositionComponent* pc = dynamic_cast<PositionComponent*>(c);
        InspectorPositionWidget* w = new InspectorPositionWidget(_mainWindow,pc->GetPosition(), c->GetID(),parent,c->name());
        QObject::connect(w,SIGNAL(applyPosition(Vector,QUuid,QUuid,QString)),
                         this,SLOT(applyPosition(Vector,QUuid,QUuid,QString)));
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::LIGHT:
    {
        LightComponent* lc = dynamic_cast<LightComponent*>(c);
        InspectorLightWidget* w = new InspectorLightWidget(_mainWindow,c->GetID(),parent,lc->GetAmbientColor(),lc->GetDiffuseColor(),lc->GetSpecularColor(),lc->GetSpotlightDirection(),lc->GetLightSourceType(),c->name());
        QObject::connect(w,SIGNAL(applyColor(Color,Color,Color,Vector,LightSourceType,QUuid,QUuid,QString)),
                         this,SLOT(applyColor(Color,Color,Color,Vector,LightSourceType,QUuid,QUuid,QString)));
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::TEXTURE:
    {
        InspectorTextureWidget* w = new InspectorTextureWidget(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::SOUND:
    {
        InspectorSoundWidget* w = new InspectorSoundWidget(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::SHADER:
    {
        InspectorShaderWidget* w = new InspectorShaderWidget(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
        break;
    }
    case ComponentType::SCRIPT:
    {
        InspectorScriptComponent* w = new InspectorScriptComponent(_mainWindow, c->GetID(),parent,c->name());
        in->addWidget(w);
        _inspectorWidgets.append(w);
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
    _inspectorWidgets.clear();
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

void GEENIE::insertDockWidget(EDockWidgetTypes type, QWidget *widget, bool show, Qt::DockWidgetArea area, bool floating, int width, int height, int x, int y)
{
    if(!_dockWidgets.contains(type))
    {
        GDockWidget* dWidget = new GDockWidget(_dockWidgetsTitles.value(type),_mainWindow);
        widget->setParent(dWidget);
        if(floating)
        {
            dWidget->setGeometry(x,y,width,height);
        }
        else
        {
            dWidget->setGeometry(0,0,width,height);
        }
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
            _mainWindow->setDockActionsChecked(type,show);
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
    _dockWidgetsTitles.insert(EDockWidgetTypes::EntitiesWidget,QString("Explorer"));
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
        script.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(new QString(),QIODevice::Text);
        ts.setDevice(&script);
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
        dockable->SetAttribute("x",dynamic_cast<QDockWidget*>(it.value())->x());
        dockable->SetAttribute("y",dynamic_cast<QDockWidget*>(it.value())->y());

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

#include "useractions.h"

void GEENIE::applyColor(Color ambient, Color diffuse, Color specular, Vector spot, LightSourceType type, QUuid id, QUuid parentId, QString name)
{
    LightComponent* lc = new LightComponent(type,ambient,diffuse,specular,spot,id,name);
    ModifyEntityAction* mea = new ModifyEntityAction((*_project),parentId,id,lc);
    _project->AddUserAction(mea);
    fillSceneExplorer();
}

void GEENIE::applyPosition(Vector position, QUuid id, QUuid parentId, QString name)
{
    PositionComponent* pc = new PositionComponent(position,id,name);
    ModifyEntityAction* mea = new ModifyEntityAction((*_project),parentId,id,pc);
    _project->AddUserAction(mea);
    fillSceneExplorer();
}
