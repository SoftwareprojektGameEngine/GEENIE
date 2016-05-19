#include "assets.h"

ModelAsset::ModelAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

ModelAsset::~ModelAsset() {

}

QUuid ModelAsset::GetID() {
    return this->id;
}

QString ModelAsset::GetPath() {
    return this->path;
}

AssetType ModelAsset::GetType() {
    return MODEL_ASSET;
}
