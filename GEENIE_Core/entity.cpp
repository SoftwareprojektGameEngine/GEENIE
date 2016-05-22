#include "core.h"

Entity::Entity(QUuid parentID) : parentID(parentID), components(), subEntities() {
    this->id = QUuid::createUuid();
}

Entity::~Entity() {
    foreach(Entity* subEntity, this->subEntities) {
        delete subEntity;
    }

    foreach(Component* component, this->components) {
        delete component;
    }
}

QUuid Entity::GetID() {
    return this->id;
}

QUuid Entity::GetParentID() {
    return this->parentID;
}

Entity* Entity::GetSubEntity(const QUuid& entityID) {
    return this->subEntities.value(entityID, nullptr);
}

QHashIterator<QUuid, Entity*> Entity::GetSubEntities() {
    return QHashIterator<QUuid, Entity*>(this->subEntities);
}

void Entity::AddSubEntity(Entity* entity) {
    if (entity == nullptr) return;

    this->subEntities.insert(entity->GetID(), entity);
}

Entity* Entity::RemoveSubEntity(const QUuid& entityID) {
    Entity* entity = this->subEntities.value(entityID, nullptr);
    if (entity != nullptr) {
        this->subEntities.remove(entityID);
    }
    return entity;
}

Component* Entity::GetComponent(const QUuid &componentID) {
    return this->components.value(componentID, nullptr);
}

QHashIterator<QUuid, Component*> Entity::GetComponents() {
    return QHashIterator<QUuid, Component*>(this->components);
}

void Entity::AddComponent(Component *component) {
    if (component == nullptr) return;

    this->components.insert(component->GetID(), component);
}

Component* Entity::RemoveComponent(const QUuid &componentID) {
    Component* component = this->components.value(componentID, nullptr);
    if (component != nullptr) {
        this->components.remove(componentID);
    }
    return component;
}