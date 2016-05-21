#include "assets.h"

ModelAsset::ModelAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
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
