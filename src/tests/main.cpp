#include <QTest>

#include "application.h"

#include "test_gameobject.h"
#include "test_gameobjectclass.h"


int main(int argc, char *argv[]) {

    Application application(argc, argv);

    QTest::qExec(new GameObjectClassTest());
    QTest::qExec(new GameObjectTest());

    return 0;
}
