#ifndef MOCKENGINE_H
#define MOCKENGINE_H

#include <QObject>

#include "iengine.h"


class MockEngine : public QObject, public IEngine {

    Q_OBJECT

    public:
        MockEngine();
        virtual ~MockEngine();
};

#endif // MOCKENGINE_H
