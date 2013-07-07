#include "gameexception.h"


const QString GameException::s_messages[] = {
    QStringLiteral("Unknown game object type"),
    QStringLiteral("Invalid game object file name"),
    QStringLiteral("Cannot open game object file"),
    QStringLiteral("Invalid game object data"),
    QStringLiteral("Invalid user string format"),
    QStringLiteral("Invalid JSON format"),
    QStringLiteral("Not supported"),
    QStringLiteral("Serialization exception"),
    QStringLiteral("Could not write save data")
};


GameException::GameException(Cause cause) :
    std::exception(),
    m_cause(cause),
    m_what(s_messages[cause].toUtf8()) {
}

GameException::GameException(GameException::Cause cause, const QString &message) :
    std::exception(),
    m_cause(cause),
    m_what(QStringLiteral("%1: %2").arg(s_messages[cause], message).toUtf8()) {
}

GameException::~GameException() throw () {
}

const char *GameException::what() const throw () {

    return m_what.constData();
}
