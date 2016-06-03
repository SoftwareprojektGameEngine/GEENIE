#include "assets.h"

TextureAsset::TextureAsset(QString path, QUuid id) {
    this->path = path;
    this->id = id;
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
