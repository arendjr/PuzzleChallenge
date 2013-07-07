#include "metatyperegistry.h"

#include <QMetaType>
#include <QtQml>

#include "gameobjectclass.h"
#include "point2d.h"
#include "vector2d.h"


#define REGISTER_META_TYPE(x) {                                                                   \
    qRegisterMetaType<x>();                                                                       \
}

#define REGISTER_META_TYPE_POINTER(x) {                                                           \
    qRegisterMetaType<x *>();                                                                     \
}

#define REGISTER_SERIALIZABLE_META_TYPE(x) {                                                      \
    qRegisterMetaType<x>();                                                                       \
    UserStringConverters userStringConverters;                                                    \
    userStringConverters.typeToUserStringConverter = convert##x##ToUserString;                    \
    userStringConverters.userStringToTypeConverter = convertUserStringTo##x;                      \
    s_userStringConvertersMap.insert(#x, userStringConverters);                                   \
    JsonConverters jsonConverters;                                                                \
    jsonConverters.typeToJsonValueConverter = convert##x##ToJsonValue;                            \
    jsonConverters.jsonValueToTypeConverter = convertJsonValueTo##x;                              \
    jsonConverters.typeToJsonVariantConverter = convert##x##ToJsonVariant;                        \
    jsonConverters.jsonVariantToTypeConverter = convertJsonVariantTo##x;                          \
    s_jsonConvertersMap.insert(#x, jsonConverters);                                               \
}

#define REGISTER_QML_TYPE(x) {                                                                    \
    qmlRegisterType<x>("nl.xiaogame.components", 1, 0, #x);                                       \
}


QMap<QString, MetaTypeRegistry::UserStringConverters> MetaTypeRegistry::s_userStringConvertersMap;
QMap<QString, MetaTypeRegistry::JsonConverters> MetaTypeRegistry::s_jsonConvertersMap;


void MetaTypeRegistry::registerMetaTypes() {

    REGISTER_SERIALIZABLE_META_TYPE(AnimationType)
    REGISTER_SERIALIZABLE_META_TYPE(MovementType)
    REGISTER_SERIALIZABLE_META_TYPE(ObjectFlags)
    REGISTER_SERIALIZABLE_META_TYPE(Point2D)
    REGISTER_SERIALIZABLE_META_TYPE(Point2DList)
    REGISTER_SERIALIZABLE_META_TYPE(Vector2D)
}

MetaTypeRegistry::UserStringConverters MetaTypeRegistry::userStringConverters(const char *type) {

    if (type) {
        QString key(type);
        if (s_userStringConvertersMap.contains(key)) {
            return s_userStringConvertersMap[key];
        }
    }

    UserStringConverters converters;
    converters.typeToUserStringConverter = nullptr;
    converters.userStringToTypeConverter = nullptr;
    return converters;
}

MetaTypeRegistry::JsonConverters MetaTypeRegistry::jsonConverters(const char *type) {

    if (type) {
        QString key(type);
        if (s_jsonConvertersMap.contains(key)) {
            return s_jsonConvertersMap[key];
        }
    }

    JsonConverters converters;
    converters.typeToJsonValueConverter = nullptr;
    converters.jsonValueToTypeConverter = nullptr;
    return converters;
}
