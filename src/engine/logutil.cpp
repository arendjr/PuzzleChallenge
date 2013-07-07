#include "logutil.h"

#include <iostream>

#include <QDebug>


void LogUtil::logDebug(const QString &message) {

    QByteArray byteArray = message.toUtf8();
    qDebug() << byteArray.constData();
}

void LogUtil::logDebug(const char *message) {

    qDebug() << message;
}

void LogUtil::logInfo(const QString &message) {

    QByteArray byteArray = message.toUtf8();
    std::cout << byteArray.constData() << std::endl;
}

void LogUtil::logInfo(const char *message) {

    std::cout << message << std::endl;
}

void LogUtil::logError(const QString &message) {

    QByteArray byteArray = message.toUtf8();
    qWarning() << byteArray.constData();
}

void LogUtil::logError(const char *message) {

    qWarning() << message;
}
