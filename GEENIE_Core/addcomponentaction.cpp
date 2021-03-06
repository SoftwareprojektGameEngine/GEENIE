#include "useractions.h"

AddComponentAction::AddComponentAction(Project &project, QUuid entityID, Component *component)
    : project(project), entityID(entityID)
{
    this->component = component;
    this->done = false;
}

AddComponentAction::~AddComponentAction() {
    // delete only if not used
    if(!this->done) {
        delete this->component;
    }
}

void AddComponentAction::Do() {
    if(this->done) return;

    Entity* entity = project.FindEntity(this->entityID);

    if(entity != nullptr) {
        entity->AddComponent(this->component);
        this->done = true;
    } else {
        throw std::exception("entity not found");
    }
}

void AddComponentAction::Undo() {
    if (this->done) {
        Entity* entity = project.FindEntity(this->entityID);
        entity->RemoveComponent(this->component->GetID());
    }
    this->done = false;
}
