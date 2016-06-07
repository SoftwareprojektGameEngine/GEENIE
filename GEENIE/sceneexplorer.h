#ifndef SCENEEXPLORER_H
#define SCENEEXPLORER_H

#include <QWidget>
#include <QUuid>
#include <qtreewidget.h>

typedef int SCENEID;
typedef int ENTITYID;
typedef int COMPONENTID;

struct COMPONENT_DATA
{
    QString componentName;
    QUuid entityId;
	QUuid componentId;
};

struct ENTITY_DATA
{
    QString entityName;
    QUuid   entityId;
    QList<ENTITY_DATA> entities;
    QList<COMPONENT_DATA> components;

};

struct SCENE_DATA
{
    QString sceneName;
    QUuid sceneId;
    QList<ENTITY_DATA> entities;
};

enum{SE_INVALID_NAME = -10, SE_INVALID_SCENEID, SE_INVALID_ENTITYID, SE_INVALID_COMPONENTID, SE_TAKE_ERROR, SE_INVALID_ENTITY_COUNT};

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


    int AddScene(QString sceneName, QUuid id);
    int AddEntitys(QTreeWidgetItem*,QList<ENTITY_DATA>);
    int AddComponent();
    int FillTree(QList<SCENE_DATA>*);

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
    void ContextMenuRenameEntity();
    void ContextMenuDeleteEntity();

signals:
    void clicked(QUuid id, se::ItemType type);
    void clicked(QUuid id, se::ItemType type, QUuid parentId);
    void CMPreviewScene(QUuid);
    void CMRenameScene(QUuid);
    void CMDeleteScene(QUuid);
    void CMAddEntity(QUuid, se::ItemType);
    void CMAddComponent(QUuid);
    void CMDeleteComponent(QUuid,QUuid);
    void CMDeleteEntity(QUuid);
    void CMRenameEntity(QUuid);
    void sceneClicked();

private:


    Ui::SceneExplorer *ui;
};
#endif // SCENEEXPLORER_H
