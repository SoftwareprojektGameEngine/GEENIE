#ifndef SCENEEXPLORER_H
#define SCENEEXPLORER_H

#include <QWidget>
#include <QUuid>
#include <qtreewidget.h>

typedef  int SCENEID;
typedef  int ENTITYID;
typedef  int COMPONENTID;

enum{SE_INVALID_NAME = -10, SE_INVALID_SCENEID, SE_INVALID_ENTITYID, SE_INVALID_COMPONENTID, SE_TAKE_ERROR};

namespace Ui {
class SceneExplorer;
}

namespace se {
    enum ItemType {
        SCENE,
        ENTITY,
        COMPONENT
    };
}

class SceneExplorer : public QWidget
{
    Q_OBJECT

public:

    explicit SceneExplorer(QWidget *parent = 0);

    ~SceneExplorer();

    SCENEID AddScene(QString sceneName, QUuid id);
    int DeleteScene(SCENEID id);

    SCENEID AddEntity(QString entityName, SCENEID index, QUuid id);
    int DeleteEntity(SCENEID sceneId, ENTITYID entityId);

    COMPONENTID AddComponent(QString componentName, SCENEID sceneIndex, ENTITYID entityIndex, QUuid id, QUuid entityId);
    int DeleteComponent(SCENEID sceneIndex, ENTITYID entityIndex , COMPONENTID componentIndex);

    void setHeader(QString& name);

    void clear();

public slots:

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void ContextMenuPreviewScene();
    void ContextMenuRenameScene();
    void ContextMenuDeleteScene();
    void ContextMenuAddEntityToScene();
    void ContextMenuAddEntityToEntity();
    void ContextMenuAddComponent();
    void ContextMenuDeleteComponent();

signals:
    void clicked(QUuid id, se::ItemType type);
    void clicked(QUuid id, se::ItemType type, QUuid parentId);
    void CMPreviewScene(QUuid);
    void CMRenameScene(QUuid);
    void CMDeleteScene(QUuid);
    void CMAddEntity(QUuid, se::ItemType);
    void CMAddComponent(QUuid);
    void CMDeleteComponent(QUuid,QUuid);
    void sceneClicked();

private:

    Ui::SceneExplorer *ui;
};
#endif // SCENEEXPLORER_H
