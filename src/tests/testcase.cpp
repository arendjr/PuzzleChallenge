#include "testcase.h"

#include "metatyperegistry.h"


void TestCase::initTestCase() {

    MetaTypeRegistry::registerMetaTypes();
}

void TestCase::cleanupTestCase() {
}
