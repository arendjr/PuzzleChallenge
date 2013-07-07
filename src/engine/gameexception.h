#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>

#include <QByteArray>
#include <QString>


class GameException : public std::exception {

    public:
        enum Cause {
            UnknownGameObjectType = 0,
            InvalidGameObjectFileName,
            CouldNotOpenGameObjectFile,
            InvalidGameObjectData,
            InvalidUserStringFormat,
            InvalidJsonFormat,
            NotSupported,
            SerializationException,
            CouldNotWriteSaveData
        };

        GameException(Cause cause);
        GameException(Cause cause, const QString &message);
        virtual ~GameException() throw ();

        Cause cause() const { return m_cause; }

        virtual const char *what() const throw ();

    private:
        static const QString s_messages[];

        Cause m_cause;

        QByteArray m_what;
};

#endif // GAMEEXCEPTION_H
