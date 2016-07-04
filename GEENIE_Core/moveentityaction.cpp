#include "useractions.h"

MoveEntityAction::MoveEntityAction(Project& project, QUuid newParentID, QUuid entityID)
    : project(project)
{

    this->movedEntity = project.FindEntity(entityID);

    this->parentID = this->movedEntity->GetParentID();
    this->newParentID = newParentID;
    this->done = false;
}

MoveEntityAction::~MoveEntityAction()
{
    /* delete only if action not undone
    if (this->done) {
        delete this->removedEntity;
    }*/
}

void MoveEntityAction::Do()
{
    Entity *e = new Entity(this->parentID,this->movedEntity->GetID(),this->movedEntity->name());


    QHashIterator<QUuid,Component*> com = this->movedEntity->GetComponents();
    while(com.hasNext())
    {
        com.next();
        e->AddComponent(com.value());
    }
    project.RemoveEntity(this->movedEntity->GetID());
    project.AddEntity(e);

    this->movedEntity = e;
    this->done = true;
}

void MoveEntityAction::Undo()
{
    //project.AddEntity(this->movedEntity->GetID());
    this->done = false;
}
