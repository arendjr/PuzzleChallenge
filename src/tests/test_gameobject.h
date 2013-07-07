#ifndef TEST_GAMEOBJECT_H
#define TEST_GAMEOBJECT_H

#include "testcase.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>

#include "gameobject.h"
#include "gameobjectclass.h"
#include "mockengine.h"


class GameObjectTest : public TestCase {

    Q_OBJECT

    private slots:
        virtual void init() {

            m_engine = new MockEngine();
        }

        virtual void cleanup() {

            delete m_engine;
        }

        void testLoadJson() {

            QFile classFile(":/testdata/class1.json");
            classFile.open(QIODevice::ReadOnly);
            QJsonDocument document = QJsonDocument::fromJson(classFile.readAll());

            GameObjectClass objectClass;
            objectClass.loadJson(document.object());

            QFile objectFile(":/testdata/object1.json");
            objectFile.open(QIODevice::ReadOnly);
            document = QJsonDocument::fromJson(objectFile.readAll());

            GameObject object(m_engine, &objectClass, 1);
            object.loadJson(document.object());

            QCOMPARE(object.animationType(), AnimationType(AnimationType::Once));
            QCOMPARE(object.direction(), Vector2D(1, 0));
            QCOMPARE(object.flags(), ObjectFlags(ObjectFlags::Deadly));
            QCOMPARE(object.frames(), QStringLiteral("object1.png,object2.png").split(','));
            QCOMPARE(object.identifier(), QStringLiteral("Icecream"));
            QCOMPARE(object.movementType(), MovementType(MovementType::Clockwise));
            QCOMPARE(object.sprite(), QStringLiteral("object1.png"));
            QCOMPARE(object.zIndex(), 42);
        }

    private:
        MockEngine *m_engine;
};

#endif // TEST_GAMEOBJECTCLASS_H
