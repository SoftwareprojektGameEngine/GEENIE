#ifndef SCENEEXPLORER_H
#define SCENEEXPLORER_H

#include <QWidget>
#include <QUuid>
#include <qtreewidget.h>

//! Sceneid is alias for int.

typedef int SCENEID;

//! Entityid is alias for int.

typedef int ENTITYID;

//! Componentid is alias for int.

typedef int COMPONENTID;

//! Component data struct.
/*!
 * Initializes componentname, entityid and componentid.
 */

struct COMPONENT_DATA
{
    QString componentName;
    QUuid entityId;
	QUuid componentId;
};

//! Entity data struct.
/*!
 * Initializes the entityname, entityid, entities and components.
 */

struct ENTITY_DATA
{
    QString entityName;
    QUuid   entityId;
    QList<ENTITY_DATA> entities;
    QList<COMPONENT_DATA> components;

};

//! Scene data struct.
/*!
 * Initializes the scenename, sceneid and entities.
 */

struct SCENE_DATA
{
    QString sceneName;
    QUuid sceneId;
    QList<ENTITY_DATA> entities;
};

//! Anonymus enum.

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

/*!
 * \class SceneExplorer sceneexplorer.h
 * \brief The SceneExplorer class.
 */

class SceneExplorer : public QWidget
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * \param parent The parent widget.
     */

    explicit SceneExplorer(QWidget *parent = 0);

    //! Deconstructor.

    ~SceneExplorer();

    //! Is adding a new scene to the tree.
    /*!
     * \param sceneName The name of the scene.
     * \param id The id of the new scene.
     * \return Returns 0 on success or invalidname.
     */

    int AddScene(QString sceneName, QUuid id);

    //! Method to add entities to scene.
    /*!
      Adds entities, subentities and their components to the tree.
     * \return Returns 0 on success.
     */

    int AddEntitys(QTreeWidgetItem*,QList<ENTITY_DATA>);

    //! Adds a component to an entity.
    /*!
     * \return Returns 0 on success.
     */

    int AddComponent();

    //! Is filling the tree view with scenes, entities and components.

    int FillTree(QList<SCENE_DATA>*);

    void setHeader(QString& name);

    //! Clears the whole tree.

    void clear();

public slots:

private slots:

    //! Slot for the clicked signal.
    /*!
      If a scene is clicked, it emits sceneClicked, else clicked.
     * \param item The selected item in the tree.
     * \param column Column of the selected item.
     */

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    //! The context menu.
    /*!
      Depend on the position in the tree, this method is returning the right context menu.
     * \param pos Current position in the tree.
     */

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    //! Emits previewscene.

    void ContextMenuPreviewScene();

    //! Emits renamescene.

    void ContextMenuRenameScene();

    //! Emits deletescene.

    void ContextMenuDeleteScene();

    //! Emits addentity.

    void ContextMenuAddEntityToScene();

    //! Emits addentity.

    void ContextMenuAddEntityToEntity();

    //! Emits addcomponent.

    void ContextMenuAddComponent();

    //! Emits deletecomponent.

    void ContextMenuDeleteComponent();

    //! Emits renameentity.

    void ContextMenuRenameEntity();

    //! Emits deleteentity.

    void ContextMenuDeleteEntity();

    //! Emits addscene.

    void ContextMenuAddScene();

signals:

    //! Clicked signal.

    void clicked(QUuid id, se::ItemType type);

    //! Clicked signal.

    void clicked(QUuid id, se::ItemType type, QUuid parentId);

    //! Previewscene Signal.

    void CMPreviewScene(QUuid);

    //! Renamescene signal.

    void CMRenameScene(QUuid);

    //! Deletescene signal.

    void CMDeleteScene(QUuid);

    //! Addentity signal.

    void CMAddEntity(QUuid, se::ItemType);

    //! Addcomponent signal.

    void CMAddComponent(QUuid);

    //! Deletecomponent signal.

    void CMDeleteComponent(QUuid,QUuid);

    //! Deleteentity signal.

    void CMDeleteEntity(QUuid);

    //! Renameentity signal.

    void CMRenameEntity(QUuid);

    //! Addscene signal.

    void CMAddScene();

    //! Scene clicked signal.

    void sceneClicked();

private:

    //! Private variable stores the scene explorer ui.

    Ui::SceneExplorer *ui;
};
#endif // SCENEEXPLORER_H
