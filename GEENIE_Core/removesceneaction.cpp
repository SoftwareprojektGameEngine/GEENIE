#include "useractions.h"

RemoveSceneAction::RemoveSceneAction(Project& project, QUuid sceneID) : project(project) {
    this->done = false;
    this->scene = project.GetScene(sceneID);
}

RemoveSceneAction::~RemoveSceneAction() {
    if (this->done) {
        delete this->scene;
    }
}

void RemoveSceneAction::Do() {
    project.RemoveScene(this->scene->GetID());
    this->done = true;
}

void RemoveSceneAction::Undo() {
    project.AddScene(this->scene);
    this->done = false;
}
