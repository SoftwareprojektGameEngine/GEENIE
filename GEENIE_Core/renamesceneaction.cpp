#include "useractions.h"

RenameSceneAction::RenameSceneAction(Project &project, QUuid sceneID, QString name):
    project(project),
    newName(name),
    sceneID(sceneID)
{
    Scene* scene = project.GetScene(sceneID);
    if(scene != nullptr)
    {
        oldName = scene->name();
    }
    this->done = false;
}

RenameSceneAction::~RenameSceneAction()
{

}

void RenameSceneAction::Do()
{
    Scene* scene = project.GetScene(sceneID);
    if(scene != nullptr)
    {
        scene->setName(newName);
        this->done = true;
    }
}

void RenameSceneAction::Undo()
{
    Scene* scene = project.GetScene(sceneID);
    if(scene != nullptr)
    {
        scene->setName(oldName);
        this->done = false;
    }
}
