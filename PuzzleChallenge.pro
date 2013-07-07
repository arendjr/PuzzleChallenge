include(environment.pri)

TARGET = PuzzleChallenge

TEMPLATE = app

SOURCES += \
    src/application.cpp \
    src/engine/conversionutil.cpp \
    src/engine/engine.cpp \
    src/engine/gameexception.cpp \
    src/engine/gameobject.cpp \
    src/engine/gameobjectclass.cpp \
    src/engine/logutil.cpp \
    src/engine/metatyperegistry.cpp \
    src/engine/point2d.cpp \
    src/engine/util.cpp \
    src/engine/vector2d.cpp \
    src/main.cpp \

HEADERS += \
    src/application.h \
    src/engine/conversionutil.h \
    src/engine/engine.h \
    src/engine/foreach.h \
    src/engine/gameexception.h \
    src/engine/gameobject.h \
    src/engine/gameobjectclass.h \
    src/engine/iengine.h \
    src/engine/logutil.h \
    src/engine/metatyperegistry.h \
    src/engine/point2d.h \
    src/engine/util.h \
    src/engine/vector2d.h \

OTHER_FILES += \
    data/classes/blueblock.json \
    data/classes/button.json \
    data/classes/exit.json \
    data/classes/explosion.json \
    data/classes/gate.json \
    data/classes/greenball.json \
    data/classes/mine.json \
    data/classes/player.json \
    data/classes/purplecreature.json \
    data/classes/raft.json \
    data/classes/redblock.json \
    data/classes/splash.json \
    data/classes/water.json \
    data/classes/yellowblock.json \
    qml/PuzzleChallenge/MenuItem.qml \
    qml/PuzzleChallenge/Main.qml \

INCLUDEPATH += \
    src \
    src/engine \
    src/engine/logmessages \

xiaogame.source = qml/PuzzleChallenge
xiaogame.target = qml
DEPLOYMENTFOLDERS = puzzlechallenge

QML_IMPORT_PATH =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
