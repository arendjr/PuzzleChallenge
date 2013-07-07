#include <QTest>

#include "application.h"

#include "test_gameobjectclass.h"


int main(int argc, char *argv[]) {

    Application application(argc, argv);

    QTest::qExec(new GameObjectClassTest());

    return 0;
}
