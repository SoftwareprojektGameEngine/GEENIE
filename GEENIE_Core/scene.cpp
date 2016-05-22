#include "core.h"

Scene::Scene(QUuid id) : entities() {
    this->id = id;
}

Scene::~Scene() {
    foreach(Entity* entity, this->entities) {
        delete entity;
    }
}

QUuid Scene::GetID() {
    return this->id;
}

Entity* Scene::GetEntity(const QUuid& entityID) {
    return this->entities.value(entityID, nullptr);
}

QHashIterator<QUuid, Entity*> Scene::GetEntities() {
    return QHashIterator<QUuid, Entity*>(this->entities);
}

void Scene::AddEntity(Entity *entity) {
    if (entity == nullptr) return;

    this->entities.insert(entity->GetID(), entity);
}

Entity* Scene::RemoveEntity(const QUuid& entityID) {
    Entity* entity = this->entities.value(entityID, nullptr);

    if (entity != nullptr) {
        this->entities.remove(entityID);
    }

    return entity;
}
