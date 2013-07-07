#ifndef POINT2D_H
#define POINT2D_H

#include <initializer_list>

#include <QString>
#include <QVector>

#include "metatyperegistry.h"


class Point2D {

    public:
        int x;
        int y;

        Point2D() = default;
        Point2D(int x, int y);

        bool operator==(const Point2D &other) const;
        bool operator!=(const Point2D &other) const;

        static QString toUserString(const Point2D &point);
        static void fromUserString(const QString &string, Point2D &point);

        static QJsonValue toJsonValue(const Point2D &point);
        static void fromJsonValue(const QJsonValue &jsonValue, Point2D &point);
        static QVariant toJsonVariant(const Point2D &point);
        static void fromJsonVariant(const QVariant &jsonVariant, Point2D &point);
};

inline uint qHash(const Point2D &point, uint seed) {

    return qHash(point.x, seed) ^ point.y;
}

PT_DECLARE_SERIALIZABLE_METATYPE(Point2D)


class Point2DList : public QVector<Point2D> {

    public:
        Point2DList();
        Point2DList(const Point2DList &other);
        Point2DList(const QVector<Point2D> &other);
        Point2DList(const std::initializer_list<Point2D> &other);

        static QString toUserString(const Point2DList &pointList);
        static void fromUserString(const QString &string, Point2DList &pointList);

        static QJsonValue toJsonValue(const Point2DList &pointList);
        static void fromJsonValue(const QJsonValue &jsonValue, Point2DList &pointList);
        static QVariant toJsonVariant(const Point2DList &pointList);
        static void fromJsonVariant(const QVariant &jsonVariant, Point2DList &pointList);
};

PT_DECLARE_SERIALIZABLE_METATYPE(Point2DList)

#endif // POINT2D_H
