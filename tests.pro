include(PuzzleChallenge.pro)

TARGET = tests

QT += testlib

SOURCES -= \
    src/main.cpp \

SOURCES += \
    src/tests/main.cpp \
    src/tests/mockengine.cpp \
    src/tests/testcase.cpp \

HEADERS += \
    src/tests/mockengine.h \
    src/tests/testcase.h \
    src/tests/test_gameobject.h \
    src/tests/test_gameobjectclass.h \

RESOURCES += \
    src/tests/testdata.qrc \

OTHER_FILES += \
    src/tests/data/classes/class1.json \
    src/tests/data/classes/object1.json \

INCLUDEPATH += \
    src/tests \
