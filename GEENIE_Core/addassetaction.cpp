#include "useractions.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

AddAssetAction::AddAssetAction(Project& project, AssetType type, QString path) : project(project) {
    this->done = false;
    this->asset = nullptr;

    QFileInfo fileInfo(path);
    QDir assetDir(project.assetPath());

    if(!fileInfo.exists()) {
        throw std::exception("invalid file path");
    }

    if(!fileInfo.absoluteFilePath().startsWith(assetDir.absolutePath())) {
        fileInfo.setFile(assetDir.absoluteFilePath(fileInfo.fileName()));

        if(fileInfo.exists()) {
            // error, file already exists
            throw std::exception("asset file already exists!");
        }

        QFile::copy(path, fileInfo.absoluteFilePath());
    }

    switch(type)
    {
    case AssetType::TEXTURE_ASSET:
    {
        asset = new TextureAsset(assetDir.relativeFilePath(fileInfo.filePath()));
        break;
    }
    case AssetType::MODEL_ASSET:
    {
        asset = new ModelAsset(assetDir.relativeFilePath(fileInfo.filePath()));
        break;
    }
    case AssetType::MATERIAL_ASSET:
    {
        asset = new MaterialAsset(assetDir.relativeFilePath(fileInfo.filePath()));
        break;
    }
    case AssetType::SCRIPT_ASSET:
    {
        asset = new ScriptAsset(assetDir.relativeFilePath(fileInfo.filePath()));
        break;
    }
    case AssetType::AUDIO_ASSET:
    case AssetType::VIDEO_ASSET:
    {
        // not implemented
        throw std::exception("not implemented");
        break;
    }
    }
}

AddAssetAction::~AddAssetAction() {
    if (!this->done) {
        delete this->asset;
        QFile(project.assetPath() + asset->GetPath()).remove();
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
