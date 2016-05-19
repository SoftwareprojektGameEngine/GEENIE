#include "assets.h"

MaterialAsset::MaterialAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

MaterialAsset::~MaterialAsset() {

}

QUuid MaterialAsset::GetID() {
    return this->id;
}

QString MaterialAsset::GetPath() {
    return this->path;
}

AssetType MaterialAsset::GetType() {
    return MATERIAL_ASSET;
}
