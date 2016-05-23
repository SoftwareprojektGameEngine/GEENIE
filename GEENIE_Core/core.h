#ifndef CORE_H
#define CORE_H

#include "geenie_core_global.h"
#include "core_base.h"
#include <QString>
#include <QUuid>
#include <QHash>

#define MAX_NUM_USERACTIONS 20

/*!
 * \brief The ComponentType enum
 */
enum ComponentType {
    MODEL,
    MATERIAL,
    POSITION,
    LIGHT,
    TEXTURE,
    SOUND,
    SHADER,
    SCRIPT
};

enum LightSourceType {
    Stuff
};

/*!
 * \brief The UserAction class
 *
 * The UserAction class is an interface for state-changing operations on a Project instance.
 */
class SHARED_EXPORT UserAction {
public:
    //! The constructor.
    UserAction() {}
    //! The destructor.
    virtual ~UserAction() {}

    //! Executes the action.
    virtual void Do() = 0;
    //! Reverts the action.
    virtual void Undo() = 0;
};

/*!
 * \brief The Component class
 *
 * Note: This is an abstract base class and can't be instantiated directly.
 */
class SHARED_EXPORT Component {
public:
    Component() {}
    virtual ~Component() {}

    virtual QUuid GetID() = 0;
    virtual ComponentType GetType() = 0;
};

class SHARED_EXPORT Entity {
private:
    QUuid id;
    QUuid parentID;

    QHash<QUuid, Component*> components;
    QHash<QUuid, Entity*> subEntities;
public:
    Entity(QUuid parentID, QUuid id = QUuid::createUuid());
    ~Entity();

    QUuid GetID();
    QUuid GetParentID();

    Entity* GetSubEntity(const QUuid& entityID);
    QHashIterator<QUuid, Entity*> GetSubEntities();
    bool HasSubEntities();
    void AddSubEntity(Entity* entity);
    Entity* RemoveSubEntity(const QUuid& entityID);

    Component* GetComponent(const QUuid& componentID);
    QHashIterator<QUuid, Component*> GetComponents();
    void AddComponent(Component* component);
    Component* RemoveComponent(const QUuid& componentID);
    bool HasComponents();
};

class SHARED_EXPORT Scene {
private:
    QUuid id;
    QHash<QUuid, Entity*> entities;
public:
    Scene(QUuid id = QUuid::createUuid());
    ~Scene();

    QUuid GetID();

    Entity* GetEntity(const QUuid& entityID);
    QHashIterator<QUuid, Entity*> GetEntities();
    void AddEntity(Entity* entity);
    Entity* RemoveEntity(const QUuid& entityID);
    bool HasEntities();
};

#include "enginewrapper.h"

class TiXmlElement;

/*!
  The Project class. Used to contain all state of a project.
  */
class SHARED_EXPORT Project {
private:
    //! Ringbuffer structure of UserActions
    UserAction* userActions[MAX_NUM_USERACTIONS + 1];
    //! The index of the last action done
    int currentActionIndex;
    //! The index of the "first" (= current oldest) action in the ringbuffer
    int firstActionIndex;
    //! The collection of scenes.
    QHash<QUuid, Scene*> scenes;
    //! A collection of entities (used to speed up entity lookup).
    QHash<QUuid, Entity*> fastEntityLookup;
    //! The collection of assets.
    QHash<QUuid, Asset*> assets;
    EngineWrapper* engine;
    //! The project name
    QString projectName;
    TiXmlElement* subEntitiesToXml(Entity* entity);

public:
    //! The project constructor.
    Project(EngineWrapper* engine, QString name=QString("untitled"));
    //! The project destructor.
    ~Project();

    //! Adds a UserAction.
    void AddUserAction(UserAction* newAction);
    //! Signals whether a UserAction can be undone.
    bool CanUndo();
    //! Signals whether a UserAction can be redone.
    bool CanRedo();
    //! Executes the next UserAction.
    void Redo();
    //! Reverts the previous UserAction.
    void Undo();

    //! Adds an entity to the project.
    void AddEntity(Entity* entity);
    //! Removes the specified entity from the project.
    Entity* RemoveEntity(const QUuid& entityID);
    //! Searches the specified entity in the project.
    Entity* FindEntity(const QUuid& entityID);

    //! Adds a scene to the project.
    void AddScene(Scene* scene);
    //! Returns the specified scene.
    Scene* GetScene(const QUuid& sceneID);
    //! Removes the specified scene from the project.
    Scene* RemoveScene(const QUuid& sceneID);
    //! Returns an iterator over all scenes.
    QHashIterator<QUuid, Scene*> GetScenes();

    //! Adds an asset to the project.
    void AddAsset(Asset* asset);
    //! Returns the specified asset.
    Asset* GetAsset(const QUuid& assetID);
    //! Removes the specified asset from the project.
    Asset* RemoveAsset(const QUuid& assetID);
    //! Returns an iterator over all assets.
    QHashIterator<QUuid, Asset*> GetAssets();
    //! Loads project from specified file
    void load(QString& file);
    //! Saves project to specified file
    void save(QString& file);
};

#endif // CORE_H
