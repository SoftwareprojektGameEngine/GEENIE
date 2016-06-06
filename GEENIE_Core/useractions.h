#ifndef USERACTION_H
#define USERACTION_H

#include "core.h"

//! This action creates an entity.
/*!
 * This action contains all necessary state information to create
 * (or remove) an entity in a project.
 */
class SHARED_EXPORT CreateEntityAction : public UserAction {
private:
    Project& project; //!< The project in which the entity will be created.
    Entity* createdEntity; //!< A pointer to the created entity.
    QUuid parentID; //!< The id of the parent of the created entity.
    bool done; //!< The state of this action. (Needed for cleanup.)
public:
    //! The constructor
    CreateEntityAction(Project& project, QUuid parentID, QString name);
    //! The destructor
    ~CreateEntityAction();

    //! This executes the action (created the entity).
    void Do();
    //! This rolls the action back (removes the entity).
    void Undo();
};

/*!
 * \brief The RemoveEntityAction class
 */
class SHARED_EXPORT RemoveEntityAction : public UserAction {
private:
    Project& project;
    Entity* removedEntity;
    bool done;
public:
    RemoveEntityAction(Project& project, QUuid entityID);
    ~RemoveEntityAction();

    void Do();
    void Undo();
};

class SHARED_EXPORT RenameEntityAction : public UserAction {
private:
    Project& project;
    QString oldName;
    QString newName;
    QUuid entityID;
    bool done;
public:
    RenameEntityAction(Project& project, QUuid entityId, QString name);
    ~RenameEntityAction();

    void Do();
    void Undo();
};

/*!
 * \brief The AddComponentAction class
 */
class SHARED_EXPORT AddComponentAction : public UserAction {
private:
    Project& project;
    QUuid entityID;
    Component* component;
    bool done;
public:
    AddComponentAction(Project& project, QUuid entityID, Component* component);
    ~AddComponentAction();

    void Do();
    void Undo();
};

/*!
 * \brief The ModifyEntityAction class
 */
class SHARED_EXPORT ModifyEntityAction : public UserAction {
private:
    Project& project;
    QUuid entityID;
    Component* oldValue;
    Component* newValue;
    bool done;
public:
    ModifyEntityAction(Project& project, QUuid entityID, QUuid oldComponentID, Component* newValue);
    ~ModifyEntityAction();

    void Do();
    void Undo();
};

class SHARED_EXPORT RemoveComponentAction : public UserAction {
private:
    Project& project;
    QUuid entityID;
    Component* component;
    bool done;
public:
    RemoveComponentAction(Project& project, QUuid entityID, QUuid componentID);
    ~RemoveComponentAction();

    void Do();
    void Undo();
};

/*!
 * \brief The AddSceneAction class
 */
class SHARED_EXPORT AddSceneAction : public UserAction {
private:
    Project& project;
    Scene* scene;
    bool done;
public:
    AddSceneAction(Project& project, Scene* scene);
    ~AddSceneAction();

    void Do();
    void Undo();
};

/*!
 * \brief The RemoveSceneAction class
 */
class SHARED_EXPORT RemoveSceneAction : public UserAction {
private:
    Project& project;
    Scene* scene;
    bool done;
public:
    RemoveSceneAction(Project& project, QUuid sceneID);
    ~RemoveSceneAction();

    void Do();
    void Undo();
};

class SHARED_EXPORT RenameSceneAction : public UserAction {
private:
    Project& project;
    QString oldName;
    QString newName;
    bool done;
    QUuid sceneID;
public:
    RenameSceneAction(Project& project, QUuid sceneID, QString name);
    ~RenameSceneAction();

    void Do();
    void Undo();
};

/*!
 * \brief The AddAssetAction class
 */
class SHARED_EXPORT AddAssetAction : public UserAction {
private:
    Project& project;
    Asset* asset;
    bool done;
public:
    AddAssetAction(Project& project, Asset* asset);
    ~AddAssetAction();

    void Do();
    void Undo();
};

/*!
 * \brief The RemoveAssetAction class
 */
class SHARED_EXPORT RemoveAssetAction : public UserAction {
private:
    Project& project;
    Asset* asset;
    bool done;
public:
    RemoveAssetAction(Project& project, QUuid assetID);
    ~RemoveAssetAction();

    void Do();
    void Undo();
};



#endif // USERACTION_H
