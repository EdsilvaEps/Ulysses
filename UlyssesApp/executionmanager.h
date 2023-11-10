#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

//#include <QObject>
#include "type.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>


class ExecutionManager
{
//    Q_OBJECT
public:
    ExecutionManager();

    static void run(QString path, Type type);

private:

    static void openBrowser(QString link);
    static void executeProgram(QString path);
};

#endif // EXECUTIONMANAGER_H
