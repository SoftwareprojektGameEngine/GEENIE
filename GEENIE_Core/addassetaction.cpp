#include "useractions.h"

AddAssetAction::AddAssetAction(Project& project, Asset* asset) : project(project) {
    this->done = false;
    this->asset = asset;
}

AddAssetAction::~AddAssetAction() {
    if (!this->done) {
        delete this->asset;
    }
}

void AddAssetAction::Do() {
    project.AddAsset(this->asset);
    this->done = true;
}

void AddAssetAction::Undo() {
    project.RemoveAsset(this->asset->GetID());
    this->done = false;
}
