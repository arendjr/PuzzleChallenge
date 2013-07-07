#include "gameobject.h"

#include <QJsonArray>
#include <QJsonObject>

#include "conversionutil.h"
#include "gameexception.h"


GameObject::GameObject(IEngine *engine, GameObjectClass *objectClass, uint id) :
    QObject(),
    m_engine(engine),
    m_objectClass(objectClass),
    m_id(id),
    m_animationType(AnimationType::None),
    m_direction(0, 0),
    m_flags(ObjectFlags::NoFlags),
    m_identifier(""),
    m_movementType(MovementType::None),
    m_position(0, 0),
    m_sprite(""),
    m_weight(0),
    m_zIndex(0) {

    for (const QMetaProperty &meta : objectClass->metaProperties()) {
        const char *name = meta.name();
        if (property(name).isValid()) {
            setProperty(name, meta.read(objectClass));
        }
    }
}

GameObject::~GameObject() {
}

void GameObject::setAlternativeState(const QVariantMap &alternativeState) {

    m_alternativeState = alternativeState;
}

void GameObject::setAnimationType(const AnimationType &animationType) {

    m_animationType = animationType;
}

void GameObject::setDirection(const Vector2D &direction) {

    m_direction = direction;
}

void GameObject::setFlags(const ObjectFlags &flags) {

    m_flags = flags;
}

void GameObject::setFrames(const QStringList &frames) {

    m_frames = frames;
}

void GameObject::setIdentifier(const QString &identifier) {

    m_identifier = identifier;
}

void GameObject::setMovementType(const MovementType &movementType) {

    m_movementType = movementType;
}

void GameObject::setPosition(const Point2D &position) {

    m_position = position;
}

void GameObject::setSprite(const QString &sprite) {

    m_sprite = sprite;
}

void GameObject::setWeight(int weight) {

    m_weight = weight;
}

void GameObject::setZIndex(int zIndex) {

    m_zIndex = zIndex;
}

void GameObject::loadJson(const QJsonObject &jsonObject) {

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

QVector<QMetaProperty> GameObject::metaProperties() const {

    static QVector<QMetaProperty> storedProperties;
    if (storedProperties.isEmpty()) {
        int count = metaObject()->propertyCount(),
            offset = GameObject::staticMetaObject.propertyOffset();
        for (int i = offset; i < count; i++) {
            storedProperties.append(metaObject()->property(i));
        }
    }
    return storedProperties;
}
