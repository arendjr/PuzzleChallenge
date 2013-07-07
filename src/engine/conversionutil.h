#ifndef CONVERSIONUTIL_H
#define CONVERSIONUTIL_H

#include <QJsonValue>
#include <QMetaProperty>
#include <QString>
#include <QVariant>


class ConversionUtil {

    public:
        static QVariant fromJsonValue(QVariant::Type type, int userType, const QJsonValue &value);

        static QJsonValue toJsonValue(const QVariant &variant);

        static QVariant fromJsonVariant(QVariant::Type type, int userType, const QVariant &variant);

        static QVariant toJsonVariant(const QVariant &variant);

        static QString toUserString(const QVariant &variant);

        static QString jsString(QString string);
};

#endif // CONVERSIONUTIL_H
