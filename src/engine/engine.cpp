#include "engine.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QMetaType>

#include "metatyperegistry.h"



Engine::Engine() :
    QObject() {

    MetaTypeRegistry::registerMetaTypes();

    qsrand(QDateTime::currentMSecsSinceEpoch());
}

Engine::~Engine() {
}
