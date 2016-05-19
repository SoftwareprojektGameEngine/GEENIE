#include "assets.h"

TextureAsset::TextureAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

TextureAsset::~TextureAsset() {

}

QUuid TextureAsset::GetID() {
    return this->id;
}

QString TextureAsset::GetPath() {
    return this->path;
}

AssetType TextureAsset::GetType() {
    return TEXTURE_ASSET;
}
