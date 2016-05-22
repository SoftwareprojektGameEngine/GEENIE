#include "assets.h"

TextureAsset::TextureAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

TextureAsset::~TextureAsset() {

}

const QUuid TextureAsset::GetID() const {
    return this->id;
}

const QString TextureAsset::GetPath() const {
    return this->path;
}

const AssetType TextureAsset::GetType() const {
    return TEXTURE_ASSET;
}
