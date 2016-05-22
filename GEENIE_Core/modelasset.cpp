#include "assets.h"

ModelAsset::ModelAsset(QString path, QUuid id) {
    this->path = path;
    this->id = id;
}

ModelAsset::~ModelAsset() {

}

const QUuid ModelAsset::GetID() const {
    return this->id;
}

const QString ModelAsset::GetPath() const {
    return this->path;
}

const AssetType ModelAsset::GetType() const {
    return MODEL_ASSET;
}
