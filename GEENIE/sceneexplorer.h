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

public slots:

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

signals:
    void clicked(QUuid id, se::ItemType type);
    void clicked(QUuid id, se::ItemType type, QUuid parentId);

private:

    Ui::SceneExplorer *ui;
};
#endif // SCENEEXPLORER_H
