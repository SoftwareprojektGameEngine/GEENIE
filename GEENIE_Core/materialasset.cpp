#include "assets.h"

MaterialAsset::MaterialAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

MaterialAsset::~MaterialAsset() {

}

const QUuid MaterialAsset::GetID() const {
    return this->id;
}

const QString MaterialAsset::GetPath() const {
    return this->path;
}

const AssetType MaterialAsset::GetType() const {
    return MATERIAL_ASSET;
}
