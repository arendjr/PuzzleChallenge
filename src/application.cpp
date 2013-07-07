#include "application.h"

#include "gameexception.h"
#include "logutil.h"


Application::Application(int &argc, char **argv) :
    QGuiApplication(argc, argv) {
}

Application::~Application() {
}

bool Application::notify(QObject *receiver, QEvent *event) {

    try {
        return receiver->event(event);
    } catch (GameException &exception) {
        LogUtil::logError(QStringLiteral("Game Exception in event handler: %1")
                          .arg(exception.what()));
    } catch (...) {
        LogUtil::logError(QStringLiteral("Unknown exception in event handler."));
    }
    return false;
}
