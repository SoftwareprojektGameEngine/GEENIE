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

//QTEST_APPLESS_MAIN(ProjectTest)
//#include "project_test.moc"
