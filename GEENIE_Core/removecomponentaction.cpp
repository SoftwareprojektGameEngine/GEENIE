#include "useractions.h"

RemoveComponentAction::RemoveComponentAction(Project &project, QUuid entityID, QUuid componentID) :
    project(project),
    entityID(entityID)
{
    Entity* entity = project.FindEntity(entityID);
    if( entity != nullptr )
    {
        this->component = entity->GetComponent(componentID);
    }
    this->done = false;
}

RemoveComponentAction::~RemoveComponentAction()
{
    if(this->done)
    {
        delete this->component;
    }
}

void RemoveComponentAction::Do()
{
    Entity* entity = project.FindEntity(this->entityID);
    if(entity != nullptr)
    {
        entity->RemoveComponent(component->GetID());
        this->done = true;
    }
}

void RemoveComponentAction::Undo()
{
    Entity* entity = project.FindEntity(this->entityID);
    if(entity != nullptr)
    {
        entity->AddComponent(component);
    }
    this->done = false;
}
