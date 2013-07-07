#include "point2d.h"

#include <QJsonArray>
#include <QStringList>

#include "gameexception.h"
#include "util.h"


Point2D::Point2D(int x, int y) :
    x(x),
    y(y) {
}

bool Point2D::operator==(const Point2D &other) const {

    return other.x == x && other.y == y;
}

bool Point2D::operator!=(const Point2D &other) const {

    return other.x != x || other.y != y;
}

QString Point2D::toUserString(const Point2D &point) {

    return QStringLiteral("( %1, %2 )").arg(point.x).arg(point.y);
}

void Point2D::fromUserString(const QString &string, Point2D &point) {

    if (!string.startsWith(QLatin1String("(")) || !string.endsWith(QLatin1String(")"))) {
        throw GameException(GameException::InvalidUserStringFormat);
    }

    QStringList stringList = Util::splitComponents(string);
    if (stringList.length() != 2) {
        throw GameException(GameException::InvalidUserStringFormat);
    }

    point.x = stringList[0].toInt();
    point.y = stringList[1].toInt();
}

QJsonValue Point2D::toJsonValue(const Point2D &point) {

    QJsonArray array;
    array.append((double) point.x);
    array.append((double) point.y);
    return array;
}

void Point2D::fromJsonValue(const QJsonValue &jsonValue, Point2D &point) {

    QJsonArray array = jsonValue.toArray();
    if (array.size() != 2) {
        throw GameException(GameException::InvalidJsonFormat);
    }

    point.x = (int) array[0].toDouble();
    point.y = (int) array[1].toDouble();
}

QVariant Point2D::toJsonVariant(const Point2D &point) {

    QVariantList variantList;
    variantList.append(point.x);
    variantList.append(point.y);
    return variantList;
}

void Point2D::fromJsonVariant(const QVariant &jsonVariant, Point2D &point) {

    QVariantList variantList = jsonVariant.toList();
    if (variantList.length() != 2) {
        throw GameException(GameException::InvalidJsonFormat);
    }

    point.x = variantList[0].toInt();
    point.y = variantList[1].toInt();
}



Point2DList::Point2DList() :
    QVector<Point2D>() {
}

Point2DList::Point2DList(const Point2DList &other) :
    QVector<Point2D>(static_cast<const QVector<Point2D> &>(other)) {
}

Point2DList::Point2DList(const QVector<Point2D> &other) :
    QVector<Point2D>(other) {
}

Point2DList::Point2DList(const std::initializer_list<Point2D> &other) :
    Point2DList() {

    for (const Point2D &point : other) {
        append(point);
    }
}

QString Point2DList::toUserString(const Point2DList &pointList) {

    QStringList stringList;
    for (const auto &point : pointList) {
        stringList.append(Point2D::toUserString(point));
    }
    return "[ " + stringList.join(", ") + " ]";
}

void Point2DList::fromUserString(const QString &string, Point2DList &pointList) {

    Q_UNUSED(string)
    Q_UNUSED(pointList)

    throw GameException(GameException::NotSupported,
                        "Converting user strings to point list not (yet) supported");
}

QJsonValue Point2DList::toJsonValue(const Point2DList &pointList) {

    QJsonArray array;
    for (const auto &point : pointList) {
        array.append(Point2D::toJsonValue(point));
    }
    return array;
}

void Point2DList::fromJsonValue(const QJsonValue &jsonValue, Point2DList &pointList) {

    if (!jsonValue.isArray()) {
        throw GameException(GameException::InvalidJsonFormat);
    }

    for (const auto &element : jsonValue.toArray()) {
        Point2D point;
        Point2D::fromJsonValue(element, point);
        pointList.append(point);
    }
}

QVariant Point2DList::toJsonVariant(const Point2DList &pointList) {

    QVariantList variantList;
    for (const auto &point : pointList) {
        variantList.append(Point2D::toJsonVariant(point));
    }
    return variantList;
}

void Point2DList::fromJsonVariant(const QVariant &jsonVariant, Point2DList &pointList) {

    for (const auto &element : jsonVariant.toList()) {
        Point2D point;
        Point2D::fromJsonVariant(element, point);
        pointList.append(point);
    }
}

