#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>

#include "gameobjectclass.h"
#include "iengine.h"
#include "point2d.h"


class GameObject : public QObject {

    Q_OBJECT

    public:
        GameObject(IEngine *engine, GameObjectClass *objectClass, uint id);
        virtual ~GameObject();

        uint id() const { return m_id; }

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

        Point2D position() const { return m_position; }
        void setPosition(const Point2D &position);
        Q_PROPERTY(Point2D position READ position WRITE setPosition)

        QString sprite() const { return m_sprite; }
        void setSprite(const QString &sprite);
        Q_PROPERTY(QString sprite READ sprite WRITE setSprite)

        int weight() const { return m_weight; }
        void setWeight(int weight);
        Q_PROPERTY(int weight READ weight WRITE setWeight)

        int zIndex() const { return m_zIndex; }
        void setZIndex(int zIndex);
        Q_PROPERTY(int zIndex READ zIndex WRITE setZIndex)

        bool isDeadly() const { return m_flags & ObjectFlags::Deadly; }
        bool isExit() const { return m_flags & ObjectFlags::Exit; }
        bool isExplodable() const { return m_flags & ObjectFlags::Explodable; }
        bool isFloatable() const { return m_flags & ObjectFlags::Floatable; }
        bool isLiquid() const { return m_flags & ObjectFlags::Liquid; }
        bool isMovable() const { return m_flags & ObjectFlags::Movable; }
        bool isObstacle() const { return m_flags & ObjectFlags::Obstacle; }
        bool isPortable() const { return m_flags & ObjectFlags::Portable; }
        bool isTemporaryTrigger() const { return m_flags & ObjectFlags::TemporaryTrigger; }
        bool isPermanentTrigger() const { return m_flags & ObjectFlags::PermanentTrigger; }
        bool isToggleable() const { return m_flags & ObjectFlags::Toggleable; }

        void loadJson(const QJsonObject &jsonObject);

    protected:
        QVector<QMetaProperty> metaProperties() const;

    private:
        IEngine *m_engine;
        GameObjectClass *m_objectClass;
        uint m_id;

        QVariantMap m_alternativeState;
        AnimationType m_animationType;
        Vector2D m_direction;
        ObjectFlags m_flags;
        QStringList m_frames;
        QString m_identifier;
        MovementType m_movementType;
        Point2D m_position;
        QString m_sprite;
        int m_weight;
        int m_zIndex;
};

#endif // GAMEOBJECT_H
