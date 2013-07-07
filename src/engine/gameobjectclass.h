#ifndef GAMEOBJECTCLASS_H
#define GAMEOBJECTCLASS_H

#include <QObject>

#include "iengine.h"
#include "metatyperegistry.h"
#include "vector2d.h"


PT_DEFINE_ENUM(AnimationType,
    None,
    Circular,
    Random,
    Once
)

PT_DEFINE_ENUM(MovementType,
    None,
    Horizontal,
    Vertical,
    Clockwise
)

PT_DEFINE_FLAGS(ObjectFlags,
    Deadly,
    Exit,
    Floatable,
    Liquid,
    Movable,
    Obstacle,
    Player,
    Portable,
    Explodable,
    TemporaryTrigger,
    PermanentTrigger,
    Toggleable
)


class GameObjectClass : public QObject {

    Q_OBJECT

    public:
        GameObjectClass();
        virtual ~GameObjectClass();

        QVariantMap alternativeState() const { return m_alternativeState; }
        void setAlternativeState(const QVariantMap &alternativeState);
        Q_PROPERTY(QVariantMap alternativeState READ alternativeState WRITE setAlternativeState)

        AnimationType animationType() const { return m_animationType; }
        void setAnimationType(const AnimationType &animationType);
        Q_PROPERTY(AnimationType animationType READ animationType WRITE setAnimationType)

        Vector2D direction() const { return m_direction; }
        void setDirection(const Vector2D &direction);
        Q_PROPERTY(Vector2D direction READ direction WRITE setDirection)

        ObjectFlags flags() const { return m_flags; }
        void setFlags(const ObjectFlags &flags);
        Q_PROPERTY(ObjectFlags flags READ flags WRITE setFlags)

        QStringList frames() const { return m_frames; }
        void setFrames(const QStringList &frames);
        Q_PROPERTY(QStringList frames READ frames WRITE setFrames)

        QString identifier() const { return m_identifier; }
        void setIdentifier(const QString &identifier);
        Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier)

        MovementType movementType() const { return m_movementType; }
        void setMovementType(const MovementType &movementType);
        Q_PROPERTY(MovementType movementType READ movementType WRITE setMovementType)

        QString name() const { return m_name; }
        void setName(const QString &name);
        Q_PROPERTY(QString name READ name WRITE setName)

        bool showInEditor() const { return m_showInEditor; }
        void setShowInEditor(bool showInEditor);
        Q_PROPERTY(bool showInEditor READ showInEditor WRITE setShowInEditor)

        QString sprite() const { return m_sprite; }
        void setSprite(const QString &sprite);
        Q_PROPERTY(QString sprite READ sprite WRITE setSprite)

        int weight() const { return m_weight; }
        void setWeight(int weight);
        Q_PROPERTY(int weight READ weight WRITE setWeight)

        int zIndex() const { return m_zIndex; }
        void setZIndex(int zIndex);
        Q_PROPERTY(int zIndex READ zIndex WRITE setZIndex)

        void loadJson(const QJsonObject &jsonObject);

        QVector<QMetaProperty> metaProperties() const;

    private:
        QVariantMap m_alternativeState;
        AnimationType m_animationType;
        Vector2D m_direction;
        ObjectFlags m_flags;
        QStringList m_frames;
        QString m_identifier;
        MovementType m_movementType;
        QString m_name;
        bool m_showInEditor;
        QString m_sprite;
        int m_weight;
        int m_zIndex;
};

#endif // GAMEOBJECTCLASS_H
