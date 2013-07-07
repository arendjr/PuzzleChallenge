#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <QString>

#include "metatyperegistry.h"


class Vector2D {

    public:
        int x;
        int y;

        Vector2D() = default;
        Vector2D(int x, int y);

        bool operator==(const Vector2D &other) const;
        bool operator!=(const Vector2D &other) const;

        const Vector2D &operator+=(const Vector2D &other);
        const Vector2D &operator-=(const Vector2D &other);

        static QString toUserString(const Vector2D &vector);
        static void fromUserString(const QString &string, Vector2D &vector);

        static QJsonValue toJsonValue(const Vector2D &vector);
        static void fromJsonValue(const QJsonValue &jsonValue, Vector2D &vector);
        static QVariant toJsonVariant(const Vector2D &vector);
        static void fromJsonVariant(const QVariant &jsonVariant, Vector2D &vector);
};

PT_DECLARE_SERIALIZABLE_METATYPE(Vector2D)

#endif // VECTOR2D_H
