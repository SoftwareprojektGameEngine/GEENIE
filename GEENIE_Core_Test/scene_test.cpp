#include "scene_test.h"

void SceneTest::testAddEntity() {
    Scene* scene = new Scene();
    Entity* entity = new Entity(scene->GetID());

    QVERIFY(scene->GetEntity(entity->GetID()) == nullptr);
    scene->AddEntity(entity);
    QVERIFY(scene->GetEntity(entity->GetID()) == entity);

    delete scene;
}
