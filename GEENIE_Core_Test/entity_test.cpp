#include "entity_test.h"

void EntityTest::testAddEntity() {
    Entity* parent = new Entity(QUuid::createUuid());
    Entity* child = new Entity(parent->GetID());

    QVERIFY(parent->GetSubEntity(child->GetID()) == nullptr);
    QVERIFY(parent->GetID() == child->GetParentID());

    parent->AddSubEntity(child);

    QVERIFY(parent->GetSubEntity(child->GetID()) == child);

    delete parent; // autodeletes child
}

void EntityTest::testRemoveEntity() {
    Entity* parent = new Entity(QUuid::createUuid());
    Entity* child = new Entity(parent->GetID());
    parent->AddSubEntity(child);

    QVERIFY(parent->GetSubEntity(child->GetID()) == child);
    QVERIFY(parent->RemoveSubEntity(child->GetID()) == child);
    QVERIFY(parent->GetSubEntity(child->GetID()) == nullptr);

    delete child;
    delete parent;
}

void EntityTest::testGetEntity() {

}

void EntityTest::testAddComponent() {

}

void EntityTest::testRemoveComponent() {

}

void EntityTest::testGetComponent() {

}
