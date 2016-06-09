#ifndef GEENIE_H
#define GEENIE_H

#include <QObject>
#include <QMap>
#include <QString>
#include "common.h"
#include "scripthighlighter.h"
#include "sceneexplorer.h"
#include "components.h"


class GEENIEMainWindow;
class QDockWidget;
class Project;
class Entity;

enum EInspectorTypes
{
    None = 0,
    Audio = 1,
    Camera = 2,
    Material = 3,
    Texture = 4,
    Transform = 5
};

class GEENIE : public QObject
{
    Q_OBJECT
public:
    explicit GEENIE(QObject *parent = 0);
    ~GEENIE();

    void insertDockWidget(EDockWidgetTypes type, QWidget* widget, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea, bool floating = false, int width = 200, int height = 200, int x = 0, int y = 0);
    void moveDockWidget(EDockWidgetTypes type, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea, bool floating = false, int width = 200, int height = 200, int x = 0, int y = 0);

private:


    void EntityToInspector(Entity* e);
    void ComponentToInspector(Component* c, QUuid parent, bool sub = false);

    void defaultSession(QWidget* inspector, QWidget* asset, QWidget* entities);
    void createDockWidgetTitles();

    void fillSceneExplorer();
    ENTITY_DATA fillSceneExplorerWithEntities(Entity* e);

    void fillAssetWidget();

    QMap<EDockWidgetTypes, QDockWidget*> _dockWidgets;
    QMap<EDockWidgetTypes, QRect> _dockWidgetsCoords;
    QMap<EDockWidgetTypes, QString> _dockWidgetsTitles;
    QVector<QWidget*> _inspectorWidgets;

    GEENIEMainWindow* _mainWindow;
    ScriptHighlighter* _highlighter;

    QString _layoutName;

    QTimer* _saveTimer;

    Project* _project;


private slots:
    void saveSession();

    void SetDefaultLayout();

    void mainWindowOnClose();
    void ProjectConfigured();

    void saveLayout();
    void loadLayout();
    void UnsetInspector();
    void changeScriptType(Highlighter::Types type);
    void ExplorerClicked(QUuid id,se::ItemType);
    void ExplorerClicked(QUuid id,se::ItemType,QUuid parentId);

    void toggleInspectorDock(bool show);
    void toggleExplorerDock(bool show);
    void toggleConsoleDock(bool show);
    void toggleAssetDock(bool show);
    void toggleDock(EDockWidgetTypes type,bool show);

    void applyColor(Color ambient,Color diffuse,Color specular,Vector spot,LightSourceType type,QUuid id,QUuid parentId,QString name);
    void applyPosition(Vector position,QUuid id,QUuid parentId,QString name);
    void undo();
    void redo();

    void AddEntity(QUuid parentId,se::ItemType type);
    void AddScene();
    void RenameScene(QUuid id);
    void DeleteScene(QUuid id);
    void DeleteComponent(QUuid id, QUuid parentId);
    void AddComponent(QUuid parentId);
    void DeleteEntity(QUuid id);
    void RenameEntity(QUuid id);
    void NewProject();
    void SaveProject();
    void SaveProject(QString path);

    void LoadProject(QString path);

    void AddAsset(QString path, AssetType type);
    void DeleteAsset(QUuid id);

signals:

public slots:
};

#endif // GEENIE_H
