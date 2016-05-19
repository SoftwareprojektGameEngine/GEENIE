#include "useractions.h"

RemoveEntityAction::RemoveEntityAction(Project &project, QUuid entityID) : project(project) {
    this->removedEntity = project.FindEntity(entityID);
    this->done = false;
}

RemoveEntityAction::~RemoveEntityAction() {
    // delete only if action not undone
    if (this->done) {
        delete this->removedEntity;
    }
}

void RemoveEntityAction::Do() {
    project.RemoveEntity(this->removedEntity->GetID());
    this->done = true;
}

void RemoveEntityAction::Undo() {
    project.AddEntity(this->removedEntity);
    this->done = false;
}
