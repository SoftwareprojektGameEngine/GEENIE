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
    CreateEntityAction(Project& project, QUuid parentID);
    //! The destructor
    ~CreateEntityAction();

    //! This executes the action (created the entity).
    void Do();
    //! This rolls the action back (removes the entity).
    void Undo();
};

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

#endif // USERACTION_H
