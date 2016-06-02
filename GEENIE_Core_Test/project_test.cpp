#include <QtCore/QObject>
#include <QtTest>
#include "core.h"
#include "project_test.h"

int countDestructorCalls = 0;

class TestUserAction : public UserAction {
private:
    int countDone;
    int countUndone;
public:
    TestUserAction() { countDone=0; countUndone=0; }
    ~TestUserAction();

    void Do() { countDone++; }
    void Undo() { countUndone++; }

    int GetCountDone() { return countDone; }
    int GetCountUndone() { return countUndone; }
};

TestUserAction::~TestUserAction() {
    countDestructorCalls += 1;
}

void ProjectTest::testAddUserAction() {
    // prepare test action
    TestUserAction* testAction = new TestUserAction();

    QVERIFY(testAction->GetCountDone() == 0);
    QVERIFY(testAction->GetCountUndone() == 0);

    // add test action to project (the project should execute the action)
    Project* project = new Project(nullptr);
    project->AddUserAction(testAction);

    QVERIFY(testAction->GetCountDone() == 1);
    QVERIFY(testAction->GetCountUndone() == 0);

    // project destructor cleans up test action
    int prevDestructorCalls = countDestructorCalls;

    delete project;

    QVERIFY(countDestructorCalls == prevDestructorCalls + 1);
}

#define NUM_TESTUSERACTIONS 2 * MAX_NUM_USERACTIONS
void ProjectTest::testAddMultipleUserActions() {
    // create test actions
    TestUserAction* testActions[NUM_TESTUSERACTIONS];

    for(int i=0; i < NUM_TESTUSERACTIONS; i++) {
        testActions[i] = new TestUserAction();

        QVERIFY(testActions[i]->GetCountDone() == 0);
        QVERIFY(testActions[i]->GetCountUndone() == 0);
    }

    // save old destructor call count
    int prevDestructorCalls = countDestructorCalls;

    // create project, add first half of test actions
    Project* project = new Project(nullptr);

    for (int i=0; i < NUM_TESTUSERACTIONS / 2; i++) {
        project->AddUserAction(testActions[i]);

        QVERIFY(testActions[i]->GetCountDone() == 1);
        QVERIFY(testActions[i]->GetCountUndone() == 0);
        QVERIFY(project->CanRedo() == false);
    }

    // no destructor calls should have been executed yet
    QVERIFY(countDestructorCalls == prevDestructorCalls);

    // add second half of test actions
    // each addition should trigger the destructor of the oldest included test action
    for(int i = NUM_TESTUSERACTIONS / 2; i < NUM_TESTUSERACTIONS; i++) {
        project->AddUserAction(testActions[i]);

        QVERIFY(testActions[i]->GetCountDone() == 1);
        QVERIFY(testActions[i]->GetCountUndone() == 0);
        QVERIFY(project->CanRedo() == false);
        QVERIFY(countDestructorCalls == ++prevDestructorCalls);
    }

    // finally: cleanup
    // second half of destructors should be called
    delete project;
    QVERIFY(countDestructorCalls == prevDestructorCalls + (NUM_TESTUSERACTIONS / 2));
}

void ProjectTest::testCanUndoRedo() {
    // create project
    Project* project = new Project(nullptr);

    QVERIFY(project->CanRedo() == false);
    QVERIFY(project->CanUndo() == false);

    // add one test action
    project->AddUserAction(new TestUserAction());

    QVERIFY(project->CanRedo() == false);
    QVERIFY(project->CanUndo() == true);

    // undo last action (so we are at the end of the valid useraction list
    project->Undo();

    QVERIFY(project->CanRedo() == true);
    QVERIFY(project->CanUndo() == false);

    // get back to front
    project->Redo();

    QVERIFY(project->CanRedo() == false);
    QVERIFY(project->CanUndo() == true);

    // add second test action
    project->AddUserAction(new TestUserAction());

    QVERIFY(project->CanRedo() == false);
    QVERIFY(project->CanUndo() == true);

    // undo last action (so we are between those 2 test actions
    project->Undo();

    QVERIFY(project->CanRedo() == true);
    QVERIFY(project->CanUndo() == true);

    // cleanup
    delete project;
}

void ProjectTest::testUndoRedo() {
    // create project
    Project* project = new Project(nullptr);

    // add test action
    TestUserAction *action = new TestUserAction();
    project->AddUserAction(action);

    QVERIFY(action->GetCountDone() == 1);
    QVERIFY(action->GetCountUndone() == 0);

    // undo once
    project->Undo();

    QVERIFY(action->GetCountDone() == 1);
    QVERIFY(action->GetCountUndone() == 1);

    // redo once
    project->Redo();

    QVERIFY(action->GetCountDone() == 2);
    QVERIFY(action->GetCountUndone() == 1);

    //cleanup
    delete project;
}

#include <QDir>
#include <QDebug>

void ProjectTest::testLoadSave()
{
    Project* project = new Project(nullptr,QString("test"));
    QVERIFY(project->name() == QString("test"));

    Scene* scene = new Scene();
    QUuid sceneID = scene->GetID();

    project->AddScene(scene);
    Entity* entity = new Entity(scene->GetID());
    QUuid entityID = entity->GetID();
    QUuid entityParent = entity->GetParentID();
    Entity* entity2 = new Entity(scene->GetID());
    QUuid entity2ID = entity2->GetID();
    QUuid entity2Parent = entity2->GetParentID();
    Entity* entity3 = new Entity(entity->GetID());
    QUuid entity3ID = entity3->GetID();
    QUuid entity3Parent = entity3->GetParentID();
    Entity* entity4 = new Entity(entity->GetID());
    QUuid entity4ID = entity4->GetID();
    QUuid entity4Parent = entity4->GetParentID();
    Entity* entity5 = new Entity(entity->GetID());
    QUuid entity5ID = entity5->GetID();
    QUuid entity5Parent = entity5->GetParentID();
    Entity* entity6 = new Entity(entity->GetID());
    QUuid entity6ID = entity6->GetID();
    QUuid entity6Parent = entity6->GetParentID();
    Entity* entity7 = new Entity(entity->GetID());
    QUuid entity7ID = entity7->GetID();
    QUuid entity7Parent = entity7->GetParentID();

    project->AddEntity(entity);
    project->AddEntity(entity2);
    project->AddEntity(entity3);
    project->AddEntity(entity4);
    project->AddEntity(entity5);
    project->AddEntity(entity6);
    project->AddEntity(entity7);

    project->save(QString("%1\\tmp.geenie").arg(QDir::tempPath()));
    Project* project2 = new Project(nullptr);
    project2->load(QString("%1\\tmp.geenie").arg(QDir::tempPath()));
    QVERIFY(project2->name() == project->name());
    QVERIFY(project2->GetScene(sceneID) != nullptr);
    QVERIFY(project2->FindEntity(entityID) != nullptr);
    QVERIFY(project2->FindEntity(entityID)->GetParentID() == entityParent);
    QVERIFY(project2->FindEntity(entity2ID) != nullptr);
    QVERIFY(project2->FindEntity(entity2ID)->GetParentID() == entity2Parent);
    QVERIFY(project2->FindEntity(entity3ID) != nullptr);
    QVERIFY(project2->FindEntity(entity3ID)->GetParentID() == entity3Parent);
    QVERIFY(project2->FindEntity(entity4ID) != nullptr);
    QVERIFY(project2->FindEntity(entity4ID)->GetParentID() == entity4Parent);
    QVERIFY(project2->FindEntity(entity5ID) != nullptr);
    QVERIFY(project2->FindEntity(entity5ID)->GetParentID() == entity5Parent);
    QVERIFY(project2->FindEntity(entity6ID) != nullptr);
    QVERIFY(project2->FindEntity(entity6ID)->GetParentID() == entity6Parent);
    QVERIFY(project2->FindEntity(entity7ID) != nullptr);
    QVERIFY(project2->FindEntity(entity7ID)->GetParentID() == entity7Parent);

    delete project2;
    delete project;
}

void ProjectTest::testAddScene() {
    Project* project = new Project(nullptr);

    Scene* scene = new Scene();
    QVERIFY(project->GetScene(scene->GetID()) == nullptr);

    project->AddScene(scene);
    QVERIFY(project->GetScene(scene->GetID()) == scene);

    delete project;
}

void ProjectTest::testRemoveScene() {
    Project* project = new Project(nullptr);

    Scene* scene = new Scene();
    project->AddScene(scene);
    QVERIFY(project->GetScene(scene->GetID()) == scene);

    QVERIFY(project->RemoveScene(scene->GetID()) == scene);
    QVERIFY(project->GetScene(scene->GetID()) == nullptr);

    delete scene;
    delete project;
}

void ProjectTest::testAddAsset() {
    Project* project = new Project(nullptr);

    Asset* testAsset = new ScriptAsset(QString("dummypath"));
    QVERIFY(project->GetAsset(testAsset->GetID()) == nullptr);

    project->AddAsset(testAsset);
    QVERIFY(project->GetAsset(testAsset->GetID()) == testAsset);

    delete project;
}

void ProjectTest::testRemoveAsset() {
    Project* project = new Project(nullptr);

    Asset* testAsset = new ScriptAsset(QString("dummypath"));
    project->AddAsset(testAsset);
    QVERIFY(project->GetAsset(testAsset->GetID()) == testAsset);

    QVERIFY(project->RemoveAsset(testAsset->GetID()) == testAsset);
    QVERIFY(project->GetAsset(testAsset->GetID()) == nullptr);

    delete testAsset;
    delete project;
}

//QTEST_APPLESS_MAIN(ProjectTest)
//#include "project_test.moc"
