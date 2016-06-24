#include "useractions.h"
#include <QDebug>
ModifyEntityAction::ModifyEntityAction(Project &project, QUuid entityID, QUuid oldComponentID, Component *newValue) : project(project), entityID(entityID) {
    this->newValue = newValue;
    Entity* entity = project.FindEntity(entityID);
    if (entity != nullptr) {
        this->oldValue = entity->GetComponent(oldComponentID);
    }
    this->done = false;
}

ModifyEntityAction::~ModifyEntityAction() {
    if (this->done) {
        delete this->oldValue;
    } else {
        delete this->newValue;
    }
}

void ModifyEntityAction::Do() {
    Entity* entity = project.FindEntity(this->entityID);

    if (entity != nullptr) {
        if (this->oldValue != nullptr) {
            entity->RemoveComponent(this->oldValue->GetID());
        }
        entity->AddComponent(this->newValue);

        this->done = true;
    }
}

void ModifyEntityAction::Undo() {
    Entity* entity = project.FindEntity(this->entityID);

    if (entity != nullptr) {
        if (this->newValue != nullptr) {
            entity->RemoveComponent(this->newValue->GetID());
        }

        entity->AddComponent(this->oldValue);
    }

    this->done = false;
}
