#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include <QObject>
#include "type.h"

class ExecutionManager
{
    Q_OBJECT
public:
    ExecutionManager();

    void run(QString path, Type::type type);

private:

    void openBrowser(QString link);
    void executeProgram(QString path);
};

#endif // EXECUTIONMANAGER_H
