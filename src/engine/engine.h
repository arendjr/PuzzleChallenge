#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

#include "iengine.h"


class Engine : public QObject, public IEngine {

    Q_OBJECT

    public:
        Engine();
        virtual ~Engine();
};

#endif // ENGINE_H
