#include "useractions.h"

RenameEntityAction::RenameEntityAction(Project &project, QUuid entityId, QString name):
    project(project),
    newName(name),
    entityID(entityId)
{
    Entity* entity = project.FindEntity(entityID);
    if(entity != nullptr)
    {
        oldName = entity->name();
    }
    this->done = false;
}

RenameEntityAction::~RenameEntityAction()
{

}

void RenameEntityAction::Do()
{
    Entity* entity = project.FindEntity(this->entityID);
    if(entity != nullptr)
    {
        entity->setName(newName);
        this->done = true;
    }
}

void RenameEntityAction::Undo()
{
    Entity* entity = project.FindEntity(entityID);
    if(entity != nullptr)
    {
        entity->setName(oldName);
        this->done = false;
    }
}
