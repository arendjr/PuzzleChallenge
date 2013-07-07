#ifndef LOGUTIL_H
#define LOGUTIL_H

#include <QString>


class LogUtil {

    public:
        static void logDebug(const QString &message);
        static void logDebug(const char *message);

        static void logInfo(const QString &message);
        static void logInfo(const char *message);

        static void logError(const QString &message);
        static void logError(const char *message);
};

#endif // LOGUTIL_H
