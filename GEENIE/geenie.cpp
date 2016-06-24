#include "geenie.h"
#include "common.h"
#include "geeniemainwindow.h"
#include "assetwidget.h"
#include "sceneexplorer.h"
#include "../tinyxml/tinyxml.h"
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

#include "osgwrapper.h"

GEENIE::GEENIE(QObject *parent) :
    QObject(parent),
    _layoutName("default")//,
    //_highlighter(new ScriptHighlighter(_mainWindow->scriptEditorDocument()))
{
    _engine = new OSGWrapper();
    _mainWindow = new GEENIEMainWindow(_engine);
    //EXAMPLE PROJECT
    _project = new Project(0,QString("Example project"));
    {
        Scene* scene = new Scene(QUuid::createUuid(),QString("Example Scene 1"));
        _project->AddScene(scene);
        //ModelAsset *baseModel = new ModelAsset(QString(""));
        //_project->AddAsset(baseModel);
        QUuid modelID = QUuid::createUuid();
        Entity* e1 = new Entity(scene->GetID(),QUuid::createUuid(),QString("Example Entity 1"));
        e1->AddComponent(new ModelComponent(modelID));
        e1->AddComponent(new PositionComponent(Vector{0.0f,0.0f,3.0f}));
        _project->AddEntity(e1);
        Entity* e2 = new Entity(scene->GetID(),QUuid::createUuid(),QString("Example Entity 2"));
        e2->AddComponent(new LightComponent(LightSourceType::AMBIENT,Color(),Color(),Color()));
        e2->AddComponent(new PositionComponent(Vector()));
        _project->AddEntity(e2);
        Entity* e3 = new Entity(scene->GetID(),QUuid::createUuid(),QString("Example Entity 3"));
        e2->AddComponent(new LightComponent(LightSourceType::AMBIENT,Color(0.1f,0.2f,0.4f,1.0f),Color(0.4f,0.3f,0.1f,0.9f),Color(0.7f,0.6f,0.1f,0.7f)));
        e2->AddComponent(new PositionComponent(Vector()));
        _project->AddEntity(e3);
        Entity* e4 = new Entity(e1->GetID(),QUuid::createUuid(),QString("Example Entity 4"));
        _project->AddEntity(e4);
        Entity* e5 = new Entity(e1->GetID(),QUuid::createUuid(),QString("Example Entity 5"));
        _project->AddEntity(e5);
        Scene* scene2 = new Scene(QUuid::createUuid(),QString("Example Scene 2"));
        _project->AddScene(scene2);
        Entity* e6 = new Entity(scene->GetID(),QUuid::createUuid(),QString("Example Entity 6"));
        e6->AddComponent(new ModelComponent(modelID));
        e6->AddComponent(new PositionComponent(Vector{1.0f,0.0f,3.0f}));
        _project->AddEntity(e6);
        _project->save(QString("C:/Projects/default.geenie"));

        _mainWindow->getSceneEditWidget()->GetEngineWidget()->BuildSceneGraph(scene);
    }

    _highlighter = new ScriptHighlighter(_mainWindow->scriptEditorDocument());

    createDockWidgetTitles();
    QDir dir;
    dir.mkpath(Common::log_path);

    InspectorWidget* inspectorWidget = new InspectorWidget(_mainWindow);

    QObject::connect(inspectorWidget,SIGNAL(RenameEntity(QUuid,QString)),this,SLOT(RenameEntity(QUuid,QString)));
    QObject::connect(inspectorWidget,SIGNAL(ModifyComponent(QUuid,QUuid,Component*)),this,SLOT(ModifyComponent(QUuid,QUuid,Component*)));

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
    QObject::connect(_mainWindow,SIGNAL(saveLayout()),this,SLOT(saveLayout()));
    QObject::connect(_mainWindow,SIGNAL(loadLayout()),this,SLOT(loadLayout()));
    QObject::connect(_mainWindow,SIGNAL(changeScriptType(Highlighter::Types)),
                     this,SLOT(changeScriptType(Highlighter::Types)));
    QObject::connect(_mainWindow,SIGNAL(toggleDock(EDockWidgetTypes,bool)),
                     this,SLOT(toggleDock(EDockWidgetTypes,bool)));
    QObject::connect(eWidget,SIGNAL(clicked(QUuid,se::ItemType)),this,SLOT(ExplorerClicked(QUuid,se::ItemType)));
    QObject::connect(eWidget,&SceneExplorer::sceneClicked,this,[=](QUuid q){UnsetInspector();});
    QObject::connect(eWidget,SIGNAL(sceneClicked(QUuid)),_mainWindow->getSceneEditWidget(),SLOT(setScene(QUuid)));
    QObject::connect(eWidget,SIGNAL(CMPreviewScene(QUuid)),_mainWindow->getSceneEditWidget(),SLOT(setScene(QUuid)));
    QObject::connect(eWidget,SIGNAL(CMAddComponent(QUuid)),this,SLOT(AddComponent(QUuid)));
    QObject::connect(eWidget,SIGNAL(CMAddEntity(QUuid,se::ItemType)),this,SLOT(AddEntity(QUuid,se::ItemType)));
    QObject::connect(eWidget,SIGNAL(CMAddScene()),this,SLOT(AddScene()));
    QObject::connect(eWidget,SIGNAL(CMDeleteComponent(QUuid,QUuid)),this,SLOT(DeleteComponent(QUuid,QUuid)));
    QObject::connect(eWidget,SIGNAL(CMDeleteEntity(QUuid)),this,SLOT(DeleteEntity(QUuid)));
    QObject::connect(eWidget,SIGNAL(CMDeleteScene(QUuid)),this,SLOT(DeleteScene(QUuid)));
    //QObject::connect(eWidget,SIGNAL(CMRenameEntity(QUuid)),this,SLOT(RenameEntity(QUuid)));
    QObject::connect(eWidget,SIGNAL(CMRenameScene(QUuid)),this,SLOT(RenameScene(QUuid)));

    QObject::connect(aWidget,SIGNAL(AddAssetToProject(QString,AssetType)),this,SLOT(AddAsset(QString,AssetType)));
    QObject::connect(aWidget,SIGNAL(DeleteAsset(QUuid)),this,SLOT(DeleteAsset(QUuid)));
    UnsetInspector();
    fillSceneExplorer();
    _mainWindow->show();
    QObject::connect(_mainWindow,SIGNAL(redo()),this,SLOT(redo()));
    QObject::connect(_mainWindow,SIGNAL(undo()),this,SLOT(undo()));
    QObject::connect(_mainWindow,SIGNAL(newProject()),this,SLOT(NewProject()));
    QObject::connect(_mainWindow,SIGNAL(newScene()),this,SLOT(AddScene()));
    QObject::connect(_mainWindow,SIGNAL(onClose()),this,SLOT(mainWindowOnClose()));
    QObject::connect(_mainWindow,SIGNAL(saveProject()),this,SLOT(SaveProject()));
    QObject::connect(_mainWindow,SIGNAL(saveProject(QString)),this,SLOT(SaveProject(QString)));
    QObject::connect(_mainWindow,SIGNAL(loadProject(QString)),this,SLOT(LoadProject(QString)));
    QObject::connect(_mainWindow,SIGNAL(checkIfProjectConfigured()),this,SLOT(ProjectConfigured()));
    QObject::connect(_mainWindow,SIGNAL(setLayoutToDefault()),this,SLOT(SetDefaultLayout()));

}

GEENIE::~GEENIE()
{
    _saveTimer->stop();
    delete _saveTimer;
}

void GEENIE::mainWindowOnClose()
{
    if(_project == nullptr)
    {
        _mainWindow->setProjectSaved(true);
    }
    else
    {
        _mainWindow->setProjectSaved(!_project->unsavedChanges());
    }
}

void GEENIE::ProjectConfigured()
{
    _mainWindow->setProjectConfigured(!(_project == nullptr));
}

void GEENIE::SaveProject()
{
    _project->save(_project->file());
}

void GEENIE::SaveProject(QString path)
{
    _project->save(path);
}

void GEENIE::LoadProject(QString path)
{
    if(_project == nullptr)
    {
        _project = new Project(0);
    }
    else
    {
        Project* tmp = _project;
        _project = new Project(0);
        delete tmp;
    }
    _project->load(path);
    QObject::connect(_project,SIGNAL(CanRedoSignal(bool)),_mainWindow,SLOT(CanRedo(bool)));
    QObject::connect(_project,SIGNAL(CanUndoSignal(bool)),_mainWindow,SLOT(CanUndo(bool)));
    fillSceneExplorer();
    fillAssetWidget();
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

void GEENIE::toggleAssetDock(bool show)
{
    _mainWindow->setDockActionsChecked(EDockWidgetTypes::AssetsWidget,show);
}

void GEENIE::toggleConsoleDock(bool show)
{
    _mainWindow->setDockActionsChecked(EDockWidgetTypes::LoggerWidget,show);
}

void GEENIE::toggleExplorerDock(bool show)
{
    _mainWindow->setDockActionsChecked(EDockWidgetTypes::EntitiesWidget,show);
}

void GEENIE::toggleInspectorDock(bool show)
{
    _mainWindow->setDockActionsChecked(EDockWidgetTypes::InspectorWidget,show);
}

void GEENIE::ExplorerClicked(QUuid id, se::ItemType)
{
    EntityToInspector(_project->FindEntity(id));

}

void GEENIE::fillAssetWidget()
{
    AssetWidget* a = dynamic_cast<AssetWidget*>(_dockWidgets.value(EDockWidgetTypes::AssetsWidget)->widget());
    a->clear();
    QHashIterator<QUuid, Asset*> it = _project->GetAssets();
    while(it.hasNext())
    {
        it.next();
        a->AddAsset(it.value());
    }
}

void GEENIE::fillSceneExplorer()
{
    SceneExplorer *s = dynamic_cast<SceneExplorer*>(_dockWidgets.value(EDockWidgetTypes::EntitiesWidget)->widget());
    s->clear();
    if(_project == nullptr)
    {
        s->setHeader(QString("(No project configured)"));
        return;
    }
    s->setHeader(_project->name());
    QHashIterator<QUuid, Scene*> it = _project->GetScenes();
	QList<SCENE_DATA> scenes;
    while(it.hasNext())
    {
        it.next();

		SCENE_DATA scene;
		scene.sceneId = it.key();
		scene.sceneName = it.value()->name();

        QHashIterator<QUuid, Entity*> eit = it.value()->GetEntities();
        while(eit.hasNext())
        {
            eit.next();
            ENTITY_DATA entity = fillSceneExplorerWithEntities(eit.value());
			scene.entities.append(entity);
        }
		scenes.append(scene);
    }
    s->FillTree(&scenes);
}

ENTITY_DATA GEENIE::fillSceneExplorerWithEntities(Entity *e)
{
    //SceneExplorer *s = dynamic_cast<SceneExplorer*>(_dockWidgets.value(EDockWidgetTypes::EntitiesWidget)->widget());
	ENTITY_DATA entity;
	entity.entityName = e->name();
	entity.entityId = e->GetID();

    QHashIterator<QUuid, Entity*> it = e->GetSubEntities();
    while(it.hasNext())
    {
        it.next();
		ENTITY_DATA subEntity = fillSceneExplorerWithEntities(it.value());
		entity.entities.append(subEntity);
    }
    QHashIterator<QUuid, Component*> cit = e->GetComponents();
    while(cit.hasNext())
    {
        cit.next();
		COMPONENT_DATA comp;
		comp.componentName = cit.value()->name();
		comp.entityId = e->GetID();
		comp.componentId = cit.value()->GetID();
    }
	return entity;
}

void GEENIE::EntityToInspector(Entity *e)
{
    InspectorWidget* in = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    in->FillTree(e);
}

void GEENIE::UnsetInspector()
{
    InspectorWidget* w = dynamic_cast<InspectorWidget*>(_dockWidgets.value(EDockWidgetTypes::InspectorWidget)->widget());
    w->children();
}

void GEENIE::defaultSession(QWidget *inspector, QWidget *asset, QWidget *entities)
{
    insertDockWidget(EDockWidgetTypes::LoggerWidget,Logger::Instance().loggerConsole,true,Qt::BottomDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::InspectorWidget,inspector,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::AssetsWidget,asset,true,Qt::RightDockWidgetArea);
    insertDockWidget(EDockWidgetTypes::EntitiesWidget,entities,true,Qt::LeftDockWidgetArea);
}

void GEENIE::SetDefaultLayout()
{
    moveDockWidget(EDockWidgetTypes::LoggerWidget,true,Qt::BottomDockWidgetArea);
    moveDockWidget(EDockWidgetTypes::InspectorWidget,true,Qt::RightDockWidgetArea);
    moveDockWidget(EDockWidgetTypes::AssetsWidget,true,Qt::RightDockWidgetArea);
    moveDockWidget(EDockWidgetTypes::EntitiesWidget,true,Qt::LeftDockWidgetArea);
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
        switch(type)
        {
        case EDockWidgetTypes::AssetsWidget:
        {
            QObject::connect(dWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(toggleAssetDock(bool)));
            break;
        }
        case EDockWidgetTypes::EntitiesWidget:
        {
            QObject::connect(dWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(toggleExplorerDock(bool)));
            break;
        }
        case EDockWidgetTypes::InspectorWidget:
        {
            QObject::connect(dWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(toggleInspectorDock(bool)));
            break;
        }
        case EDockWidgetTypes::LoggerWidget:
        {
            QObject::connect(dWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(toggleConsoleDock(bool)));
            break;
        }
        case EDockWidgetTypes::ScriptEditorWidget:
        default: break;
        }

    }
    else
    {
        ERROR_MSG(QString("MainWindow already contains type."));
    }
}

void GEENIE::moveDockWidget(EDockWidgetTypes type, bool show, Qt::DockWidgetArea area, bool floating, int width, int height, int x, int y)
{
    if(_dockWidgets.contains(type))
    {
        QDockWidget* w = _dockWidgets.value(type);
        _mainWindow->removeDockWidget(w);
        _mainWindow->addDockWidget(area,w);
        w->setVisible(show);
        w->setFloating(floating);
        if(floating)
        {
            w->setGeometry(x,y,width,height);
        }
        else
        {
            w->setGeometry(0,0,width,height);
        }
    }
}

void GEENIE::createDockWidgetTitles()
{
    _dockWidgetsTitles.insert(EDockWidgetTypes::LoggerWidget,QString("Logger"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::InspectorWidget,QString("Inspector"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::AssetsWidget,QString("Assets"));
    _dockWidgetsTitles.insert(EDockWidgetTypes::EntitiesWidget,QString("Explorer"));
}

#include <QFileDialog>

void GEENIE::saveLayout()
{
    QString file = QFileDialog::getSaveFileName(_mainWindow,tr("Save Layout"),"C:/","Layout files (*.xml)");
    if(file.isEmpty())
    {
        return;
    }
    INFO_MSG("Saving current session.");
    QFile sessionSaveFile(file);
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
    doc.SaveFile(file.toUtf8().data());
}

void GEENIE::loadLayout()
{
    QString file = QFileDialog::getOpenFileName(_mainWindow,tr("Save Layout"),"C:/","Layout files (*.xml)");
    if(file.isEmpty())
    {
        return;
    }
    INFO_MSG("Loading session save file.");
    TiXmlDocument doc(file.toUtf8().data());
    bool ok = doc.LoadFile();
    if(!ok)
    {
        ERROR_MSG("Failed to load last session. Using default.");
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
                TiXmlElement* dockArea = dockable->FirstChildElement("area");
                bool ok;
                area = (Qt::DockWidgetArea)QString(dockArea->GetText()).toInt(&ok);
                if(!ok)
                {
                    ERROR_MSG("Could not read area");
                    area = Qt::BottomDockWidgetArea;
                }
                INFO_MSG(QString("%1 has area %2.").arg(it.value()).arg(area));
                moveDockWidget(type,visible,area,floating,width,height,x,y);
            }
        }
    }
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

void GEENIE::undo()
{
    _project->Undo();
    fillSceneExplorer();
    fillAssetWidget();
}

void GEENIE::redo()
{
    _project->Redo();
    fillSceneExplorer();
    fillAssetWidget();
}

#include "useractions.h"

void GEENIE::ModifyComponent(QUuid id, QUuid parentId, Component *component)
{
    ModifyEntityAction* mea = new ModifyEntityAction((*_project),parentId,id,component);
    _project->AddUserAction(mea);
    fillSceneExplorer();
}

#include "addcomponentdialog.h"
#include "addentitydialog.h"
#include "renameentitydialog.h"
#include "renamescenedialog.h"
#include "newprojectdialog.h"
#include "addscenedialog.h"
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>

void GEENIE::NewProject()
{
    NewProjectDialog n(_mainWindow);
    if(n.exec() == QDialog::Accepted)
    {
        Project* tmp = _project;
        _project = new Project(0,n.name(),n.file());
        delete tmp;
        QObject::connect(_project,SIGNAL(CanRedoSignal(bool)),_mainWindow,SLOT(CanRedo(bool)));
        QObject::connect(_project,SIGNAL(CanUndoSignal(bool)),_mainWindow,SLOT(CanUndo(bool)));
        QFile file(n.file());
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
        _project->save(n.file());
        fillSceneExplorer();
        fillAssetWidget();
    }
}

void GEENIE::AddScene()
{
    AddSceneDialog asd(_mainWindow);
    if(asd.exec() == QDialog::Accepted)
    {
        Scene* scene = new Scene(QUuid::createUuid(),asd.name());
        AddSceneAction* asa = new AddSceneAction((*_project),scene);
        _project->AddUserAction(asa);
        fillSceneExplorer();
        _mainWindow->getSceneEditWidget()->GetEngineWidget()->BuildSceneGraph(scene);
    }
}

void GEENIE::AddComponent(QUuid parentId)
{
    AddComponentDialog acd(_mainWindow);
    connect(&acd,SIGNAL(LoadAssetList(AddComponentDialog*,int)),this,SLOT(LoadAssetList(AddComponentDialog*, int)));
    if(acd.exec() == QDialog::Accepted)
    {
        Component* c = acd.component();
        qDebug() << __LINE__;
        AddComponentAction* aca = new AddComponentAction((*_project),parentId,c);
        _project->AddUserAction(aca);
        fillSceneExplorer();
    }
}

void GEENIE::DeleteComponent(QUuid id, QUuid parentId)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(_mainWindow,tr("Delete Component"),tr("Are you sure you want to delete this component?"),QMessageBox::No | QMessageBox::Yes);
    if(resBtn == QMessageBox::Yes)
    {
        RemoveComponentAction* rsa = new RemoveComponentAction((*_project),parentId,id);
        _project->AddUserAction(rsa);
        fillSceneExplorer();
    }
    else
    {
        return;
    }
}

void GEENIE::AddEntity(QUuid parentId, se::ItemType type)
{
    Q_UNUSED(type);

    AddEntityDialog aed(_mainWindow);
    if(aed.exec() == QDialog::Accepted)
    {
        CreateEntityAction* cea = new CreateEntityAction((*_project),parentId,aed.name());
        _project->AddUserAction(cea);
        fillSceneExplorer();
    }
}

void GEENIE::RenameScene(QUuid id)
{
    RenameSceneDialog rsd(_mainWindow,_project->GetScene(id)->name());
    if(rsd.exec() == QDialog::Accepted)
    {
        RenameSceneAction* rsa = new RenameSceneAction((*_project),id,rsd.name());
        _project->AddUserAction(rsa);
        fillSceneExplorer();
    }
}

void GEENIE::DeleteScene(QUuid id)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(_mainWindow,tr("Delete Scene"),tr("Are you sure you want to delete this scene?"),QMessageBox::No | QMessageBox::Yes);
    if(resBtn == QMessageBox::Yes)
    {
        RemoveSceneAction* rsa = new RemoveSceneAction((*_project),id);
        _project->AddUserAction(rsa);
        fillSceneExplorer();
    }
    else
    {
        return;
    }
}

void GEENIE::DeleteEntity(QUuid id)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(_mainWindow,tr("Delete Entity"),tr("Are you sure you want to delete this entity?"),QMessageBox::No | QMessageBox::Yes);
    if(resBtn == QMessageBox::Yes)
    {
        RemoveEntityAction* rea = new RemoveEntityAction((*_project),id);
        _project->AddUserAction(rea);
        fillSceneExplorer();
    }
    else
    {
        return;
    }
}

void GEENIE::RenameEntity(QUuid id, QString name)
{
    RenameEntityAction* rea = new RenameEntityAction((*_project),id,name);
    _project->AddUserAction(rea);
    fillSceneExplorer();
}


void GEENIE::AddAsset(QString path, AssetType type)
{
    if(type == AssetType::AUDIO_ASSET || type == AssetType::VIDEO_ASSET)
    {
        return;
    }

    try {
        AddAssetAction* aaa = new AddAssetAction((*_project), type, path);
        _project->AddUserAction(aaa);
        fillAssetWidget();
    } catch(const std::exception& e) {
        QMessageBox(QMessageBox::Warning, "Error", QString(e.what()), QMessageBox::Ok).exec();
    }
}

void GEENIE::DeleteAsset(QUuid id)
{
    RemoveAssetAction* raa = new RemoveAssetAction((*_project),id);
    _project->AddUserAction(raa);
    fillAssetWidget();
}

void GEENIE::LoadAssetList(AddComponentDialog* dialog,int type)
{
    QList<ASSET_DATA> assets;
    /*
    switch(type)
    {
        case MATERIAL:
        {

            break;
        }
        case POSITION:
        {

            break;
        }
        case LIGHT:
        {
            break;
        }
        case TEXTURE:
        {

            break;
        }
        case SOUND:
        {
            break;
        }
        case SHADER:
        {
            break;
        }
        case SCRIPT:
        {
            break;
        }
    }*/
    QHashIterator<QUuid,Asset*> a = _project->GetAssets();
    while(a.hasNext())
    {
        if(a.value()->GetType() == type)
        {
            ASSET_DATA data;
            data.id = a.value()->GetID();
            data.name = "Material";
            assets.push_back(data);
        }
        a.next();
    }
    dialog->SetAssetList(assets);
}
