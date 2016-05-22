#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H

#include <QObject>

class ProjectTest : public QObject {
    Q_OBJECT

public:
    ProjectTest() {}

private Q_SLOTS:
    void testAddUserAction();
    void testAddMultipleUserActions();
    void testCanUndoRedo();
    void testUndoRedo();
    //void TestUserActionEdgeCases();
};

#endif // PROJECT_TEST_H
