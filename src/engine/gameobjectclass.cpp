#include "gameobjectclass.h"

#include <QJsonObject>
#include <QVector>

#include "conversionutil.h"
#include "gameexception.h"


GameObjectClass::GameObjectClass() :
    QObject(),
    m_animationType(AnimationType::None),
    m_direction(0, 0),
    m_flags(ObjectFlags::NoFlags),
    m_identifier(""),
    m_movementType(MovementType::None),
    m_name(""),
    m_showInEditor(true),
    m_sprite(""),
    m_weight(0),
    m_zIndex(0) {
}

GameObjectClass::~GameObjectClass() {
}

void GameObjectClass::setAlternativeState(const QVariantMap &alternativeState) {

    m_alternativeState = alternativeState;
}

void GameObjectClass::setAnimationType(const AnimationType &animationType) {

    m_animationType = animationType;
}

void GameObjectClass::setDirection(const Vector2D &direction) {

    m_direction = direction;
}

void GameObjectClass::setFlags(const ObjectFlags &flags) {

    m_flags = flags;
}

void GameObjectClass::setFrames(const QStringList &frames) {

    m_frames = frames;
}

void GameObjectClass::setIdentifier(const QString &identifier) {

    m_identifier = identifier;
}

void GameObjectClass::setMovementType(const MovementType &movementType) {

    m_movementType = movementType;
}

void GameObjectClass::setName(const QString &name) {

    m_name = name;
}

void GameObjectClass::setShowInEditor(bool showInEditor) {

    m_showInEditor = showInEditor;
}

void GameObjectClass::setSprite(const QString &sprite) {

    m_sprite = sprite;
}

void GameObjectClass::setWeight(int weight) {

    m_weight = weight;
}

void GameObjectClass::setZIndex(int zIndex) {

    m_zIndex = zIndex;
}

void GameObjectClass::loadJson(const QJsonObject &jsonObject) {

    if (jsonObject.isEmpty()) {
        throw GameException(GameException::InvalidGameObjectData);
    }

    for (const QMetaProperty &meta : metaProperties()) {
        const char *name = meta.name();
        if (jsonObject.contains(name)) {
            meta.write(this, ConversionUtil::fromJsonValue(meta.type(), meta.userType(),
                                                           jsonObject[name]));
        }
    }
}

QVector<QMetaProperty> GameObjectClass::metaProperties() const {

    static QVector<QMetaProperty> storedProperties;
    if (storedProperties.isEmpty()) {
        int count = metaObject()->propertyCount(),
            offset = GameObjectClass::staticMetaObject.propertyOffset();
        for (int i = offset; i < count; i++) {
            storedProperties.append(metaObject()->property(i));
        }
    }
    return storedProperties;
}
