#include <csignal>

#include "application.h"
#include "engine.h"
#include "logutil.h"
#include "qtquick2applicationviewer.h"


void signalHandler(int param) {

    Q_UNUSED(param)

    LogUtil::logInfo("\nTerminating...");

    qApp->quit();
}

int main(int argc, char *argv[]) {

    Application application(argc, argv);

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    Engine engine;
    bool initialized = engine.init();
    if (!initialized) {
        return 1;
    }

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/XiaoGame/Main.qml"));
    viewer.showExpanded();

    return application.exec();
}
