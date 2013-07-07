#ifndef TEST_GAMEOBJECTCLASS_H
#define TEST_GAMEOBJECTCLASS_H

#include "testcase.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>

#include "gameobjectclass.h"


class GameObjectClassTest : public TestCase {

    Q_OBJECT

    private slots:
        void initTestCase() {

            MetaTypeRegistry::registerMetaTypes();
        }

        void testLoadJson() {

            QFile file(":/testdata/object1.json");
            file.open(QIODevice::ReadOnly);
            QJsonDocument document = QJsonDocument::fromJson(file.readAll());

            GameObjectClass objectClass;
            objectClass.loadJson(document.object());

            QCOMPARE(objectClass.animationType(), AnimationType(AnimationType::Once));
            QCOMPARE(objectClass.direction(), Vector2D(-1, 0));
            QCOMPARE(objectClass.flags(), ObjectFlags(ObjectFlags::Deadly | ObjectFlags::Player));
            QCOMPARE(objectClass.frames(), QStringLiteral("object1.png,object2.png").split(','));
            QCOMPARE(objectClass.identifier(), QStringLiteral("Lollypop"));
            QCOMPARE(objectClass.movementType(), MovementType(MovementType::Clockwise));
            QCOMPARE(objectClass.name(), QStringLiteral("Object One"));
            QCOMPARE(objectClass.sprite(), QStringLiteral("object1.png"));
            QCOMPARE(objectClass.zIndex(), 42);
        }
};

#endif // TEST_GAMEOBJECTCLASS_H
