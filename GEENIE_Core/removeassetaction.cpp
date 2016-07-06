#include "useractions.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>

RemoveAssetAction::RemoveAssetAction(Project& project, QUuid assetID) : project(project) {
    this->done = false;
    this->asset = project.GetAsset(assetID);
}

RemoveAssetAction::~RemoveAssetAction() {
    if (this->done) {
        QFileInfo fileInfo(project.assetPath() + asset->GetPath());
        if(fileInfo.exists()) {
            QFile(fileInfo.absoluteFilePath()).remove();
        }
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
