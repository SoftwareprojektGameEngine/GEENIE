#include <QTest>
#include "project_test.h"
#include "entity_test.h"

int main(int argc, char** argv) {
    QTest::qExec(new EntityTest());
    QTest::qExec(new ProjectTest());

    return 0;
}
