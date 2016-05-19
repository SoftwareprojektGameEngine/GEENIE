#include "useractions.h"

AddSceneAction::AddSceneAction(Project& project, Scene* scene) : project(project) {
    this->done = false;
    this->scene = scene;
}

AddSceneAction::~AddSceneAction() {
    if (!this->done) {
        delete this->scene;
    }
}

void AddSceneAction::Do() {
    project.AddScene(this->scene);
    this->done = true;
}

void AddSceneAction::Undo() {
    project.RemoveScene(this->scene->GetID());
    this->done = false;
}
