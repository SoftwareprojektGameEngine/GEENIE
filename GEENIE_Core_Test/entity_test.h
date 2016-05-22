#ifndef ENTITY_TEST_H
#define ENTITY_TEST_H

#include <QTest>
#include <QObject>

#include "core.h"

class EntityTest : public QObject {
    Q_OBJECT

public:
    EntityTest() {}

private Q_SLOTS:
    void testAddEntity();
    void testRemoveEntity();
    void testGetEntity();

    void testAddComponent();
    void testRemoveComponent();
    void testGetComponent();
};

#endif // ENTITY_TEST_H
