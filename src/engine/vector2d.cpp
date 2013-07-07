#include "vector2d.h"

#include <QJsonArray>
#include <QStringList>

#include "gameexception.h"
#include "util.h"


Vector2D::Vector2D(int x, int y) :
    x(x),
    y(y) {
}

bool Vector2D::operator==(const Vector2D &other) const {

    return other.x == x && other.y == y;
}

bool Vector2D::operator!=(const Vector2D &other) const {

    return other.x != x || other.y != y;
}

const Vector2D &Vector2D::operator+=(const Vector2D &other) {

    x += other.x;
    y += other.y;
    return *this;
}

const Vector2D &Vector2D::operator-=(const Vector2D &other) {

    x -= other.x;
    y -= other.y;
    return *this;
}

QString Vector2D::toUserString(const Vector2D &vector) {

    return QStringLiteral("[ %1, %2 ]").arg(vector.x).arg(vector.y);
}

void Vector2D::fromUserString(const QString &string, Vector2D &vector) {

    if (!string.startsWith(QLatin1String("(")) || !string.endsWith(QLatin1String(")"))) {
        throw GameException(GameException::InvalidUserStringFormat);
    }

    QStringList stringList = Util::splitComponents(string);
    if (stringList.length() != 2) {
        throw GameException(GameException::InvalidUserStringFormat);
    }

    vector.x = stringList[0].toInt();
    vector.y = stringList[1].toInt();
}

QJsonValue Vector2D::toJsonValue(const Vector2D &vector) {

    QJsonArray array;
    array.append((double) vector.x);
    array.append((double) vector.y);
    return array;
}

void Vector2D::fromJsonValue(const QJsonValue &jsonValue, Vector2D &vector) {

    QJsonArray array = jsonValue.toArray();
    if (array.size() != 2) {
        throw GameException(GameException::InvalidJsonFormat);
    }

    vector.x = (int) array[0].toDouble();
    vector.y = (int) array[1].toDouble();
}

QVariant Vector2D::toJsonVariant(const Vector2D &vector) {

    QVariantList variantList;
    variantList.append(vector.x);
    variantList.append(vector.y);
    return variantList;
}

void Vector2D::fromJsonVariant(const QVariant &jsonVariant, Vector2D &vector) {

    QVariantList variantList = jsonVariant.toList();
    if (variantList.length() != 2) {
        throw GameException(GameException::InvalidJsonFormat);
    }

    vector.x = variantList[0].toInt();
    vector.y = variantList[1].toInt();
}
