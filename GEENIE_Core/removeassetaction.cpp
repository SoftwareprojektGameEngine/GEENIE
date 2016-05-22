#include "useractions.h"

RemoveAssetAction::RemoveAssetAction(Project& project, QUuid assetID) : project(project) {
    this->done = false;
    this->asset = project.GetAsset(assetID);
}

RemoveAssetAction::~RemoveAssetAction() {
    if (this->done) {
        delete this->asset;
    }
}

void RemoveAssetAction::Do() {
    project.RemoveAsset(this->asset->GetID());
    this->done = true;
}

void RemoveAssetAction::Undo() {
    project.AddAsset(this->asset);
    this->done = false;
}
