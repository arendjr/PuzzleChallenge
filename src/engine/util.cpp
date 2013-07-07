#include "util.h"


QStringList Util::splitComponents(const QString &string) {

    QStringList components;
    QString component;
    for (int i = 1; i < string.length() - 1; i++) {
        QChar character = string[i];
        if (character == ',') {
            components.append(component);
            component.clear();
        } else if (!character.isSpace()) {
            component.append(character);
        }
    }
    components.append(component);
    return components;
}
