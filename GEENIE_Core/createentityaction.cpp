#include "useractions.h"

CreateEntityAction::CreateEntityAction(Project& project, QUuid parentID) : project(project), parentID(parentID) {
    this->done = false;
    this->createdEntity = new Entity(parentID);
}

CreateEntityAction::~CreateEntityAction() {
    // cleanup in case action was undone
    if(!this->done) {
        delete this->createdEntity;
    }
}

void CreateEntityAction::Do() {
    project.AddEntity(this->createdEntity);
    this->done = true;
}

void CreateEntityAction::Undo() {
    project.RemoveEntity(this->createdEntity->GetID());
    this->done = false;
}
