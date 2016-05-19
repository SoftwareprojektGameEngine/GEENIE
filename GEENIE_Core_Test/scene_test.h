#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include <QTest>
#include <QObject>
#include "core.h"

class SceneTest : public QObject {
    Q_OBJECT

public:
    SceneTest() {}

private Q_SLOTS:
    void testAddEntity();
};

#endif // SCENE_TEST_H
