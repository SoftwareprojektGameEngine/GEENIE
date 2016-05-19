#include "assets.h"

ScriptAsset::ScriptAsset(QString path) {
    this->path = path;
    this->id = QUuid::createUuid();
}

ScriptAsset::~ScriptAsset() {

}

QUuid ScriptAsset::GetID() {
    return this->id;
}

QString ScriptAsset::GetPath() {
    return this->path;
}

AssetType ScriptAsset::GetType() {
    return SCRIPT_ASSET;
}
