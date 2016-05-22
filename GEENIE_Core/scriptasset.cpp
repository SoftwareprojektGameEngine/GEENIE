#include "assets.h"

ScriptAsset::ScriptAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

ScriptAsset::~ScriptAsset() {

}

const QUuid ScriptAsset::GetID() const {
    return this->id;
}

const QString ScriptAsset::GetPath() const {
    return this->path;
}

const AssetType ScriptAsset::GetType() const {
    return SCRIPT_ASSET;
}
