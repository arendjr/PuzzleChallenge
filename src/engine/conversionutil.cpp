#include "conversionutil.h"

#include <QDateTime>
#include <QJsonArray>
#include <QStringList>

#include "gameexception.h"
#include "logutil.h"
#include "metatyperegistry.h"


QVariant ConversionUtil::fromJsonValue(QVariant::Type type, int userType, const QJsonValue &value) {

    switch (type) {
        case QVariant::Bool:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::Double:
        case QVariant::String:
        case QVariant::Map:
            return value.toVariant();
        case QVariant::StringList: {
            QStringList stringList;
            for (const QJsonValue &item : value.toArray()) {
                stringList.append(item.toString());
            }
            return stringList;
        }
        case QVariant::DateTime:
            return QDateTime::fromMSecsSinceEpoch((qint64) value.toDouble());
        case QVariant::UserType: {
            MetaTypeRegistry::JsonConverters converters =
                    MetaTypeRegistry::jsonConverters(QMetaType::typeName(userType));
            if (converters.jsonValueToTypeConverter) {
                return converters.jsonValueToTypeConverter(value);
            } else {
                const char *typeName = QMetaType::typeName(userType);
                throw GameException(GameException::SerializationException, typeName ?
                                    QStringLiteral("User type not serializable: %1").arg(typeName) :
                                    QStringLiteral("Unknown user type: %1").arg(userType));
            }
        }
        default:
            throw GameException(GameException::SerializationException,
                                QStringLiteral("Unknown type: %1").arg(QVariant::typeToName(type)));
    }
}

QJsonValue ConversionUtil::toJsonValue(const QVariant &variant) {

    switch (variant.type()) {
        case QVariant::Bool:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::Double:
        case QVariant::String:
        case QVariant::List:
        case QVariant::StringList:
        case QVariant::Map:
            return QJsonValue::fromVariant(variant);
        case QVariant::DateTime:
            return QJsonValue((double) variant.toDateTime().toMSecsSinceEpoch());
        case QVariant::UserType: {
            MetaTypeRegistry::JsonConverters converters =
                    MetaTypeRegistry::jsonConverters(QMetaType::typeName(variant.userType()));
            if (converters.typeToJsonValueConverter) {
                return converters.typeToJsonValueConverter(variant);
            } else {
                const char *typeName = QMetaType::typeName(variant.userType());
                LogUtil::logError(typeName ?
                                  QStringLiteral("User type not serializable: %1").arg(typeName) :
                                  QStringLiteral("Unknown user type: %1").arg(variant.userType()));
                return QJsonValue();
            }
        }
        default:
            throw GameException(GameException::SerializationException,
                                QStringLiteral("Unknown type: %1").arg(variant.typeName()));
    }
}

QVariant ConversionUtil::fromJsonVariant(QVariant::Type type, int userType,
                                         const QVariant &variant) {

    switch (type) {
        case QVariant::Bool:
        case QVariant::Int:
        case QVariant::Double:
        case QVariant::String:
            return variant;
        case QVariant::StringList:
            return variant.toStringList();
        case QVariant::DateTime:
            return QDateTime::fromMSecsSinceEpoch(variant.toLongLong());
        case QVariant::Map: {
            QVariantMap variantMap;
            QVariantMap map = variant.toMap();
            for (const QString &key : map.keys()) {
                QVariantList valueList = map[key].toList();
                if (valueList.length() == 3) {
                    QVariant::Type valueType = (QVariant::Type) valueList[0].toInt();
                    int valueUserType = valueList[1].toInt();
                    QVariant value = valueList[2];
                    variantMap[key] = fromJsonVariant(valueType, valueUserType, value);
                } else {
                    throw GameException(GameException::SerializationException,
                                        QStringLiteral("Invalid map format in key: %1").arg(key));
                }
            }
            return variantMap;
        }
        case QVariant::UserType: {
            MetaTypeRegistry::JsonConverters converters =
                    MetaTypeRegistry::jsonConverters(QMetaType::typeName(userType));
            if (converters.jsonVariantToTypeConverter) {
                return converters.jsonVariantToTypeConverter(variant);
            } else {
                const char *typeName = QMetaType::typeName(userType);
                throw GameException(GameException::SerializationException, typeName ?
                                    QStringLiteral("User type not serializable: %1").arg(typeName) :
                                    QStringLiteral("Unknown user type: %1").arg(userType));
            }
        }
        default:
            throw GameException(GameException::SerializationException,
                                QStringLiteral("Unknown type: %1").arg(QVariant::typeToName(type)));
    }
}

QVariant ConversionUtil::toJsonVariant(const QVariant &variant) {

    switch (variant.type()) {
        case QVariant::Bool:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::Double:
        case QVariant::String:
        case QVariant::List:
        case QVariant::StringList:
        case QVariant::Map:
            return variant;
        case QVariant::DateTime:
            return QVariant(variant.toDateTime().toMSecsSinceEpoch());
        case QVariant::UserType: {
            MetaTypeRegistry::JsonConverters converters =
                    MetaTypeRegistry::jsonConverters(QMetaType::typeName(variant.userType()));
            if (converters.typeToJsonVariantConverter) {
                return converters.typeToJsonVariantConverter(variant);
            } else {
                const char *typeName = QMetaType::typeName(variant.userType());
                LogUtil::logError(typeName ?
                                  QStringLiteral("User type not serializable: %1").arg(typeName) :
                                  QStringLiteral("Unknown user type: %1").arg(variant.userType()));
                return QJsonValue();
            }
        }
        default:
            throw GameException(GameException::SerializationException,
                                QStringLiteral("Unknown type: %1").arg(variant.typeName()));
    }
}

QString ConversionUtil::toUserString(const QVariant &variant) {

    if (!variant.isValid()) {
        return "(not set)";
    }

    switch (variant.type()) {
        case QVariant::Bool:
            return variant.toBool() ? "true" : "false";
        case QVariant::Int:
            return QString::number(variant.toInt());
        case QVariant::Double:
            return QString::number(variant.toDouble());
        case QVariant::String: {
            QString string = variant.toString();
            return string.isEmpty() ? "(empty string)" : string;
        }
        case QVariant::StringList:
            return variant.toStringList().join("\n");
        case QVariant::DateTime:
            return variant.toDateTime().toString();
        case QVariant::UserType: {
            MetaTypeRegistry::UserStringConverters converters =
                    MetaTypeRegistry::userStringConverters(QMetaType::typeName(variant.userType()));
            if (converters.typeToUserStringConverter) {
                return converters.typeToUserStringConverter(variant);
            }
        }   // fall-through
        default:
            return "(unknown type)";
    }
}

QString ConversionUtil::jsString(QString string) {

    return "\"" + string.replace('\\', "\\\\")
                        .replace('"', "\\\"")
                        .replace('\n', "\\n") + "\"";
}
