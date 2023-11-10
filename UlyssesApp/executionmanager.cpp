#include "executionmanager.h"
#include <QDebug>

ExecutionManager::ExecutionManager()
{

}

void ExecutionManager::run(QString path, Type type)
{
    if(type == Type::type_en::link){
        openBrowser(path);
    }

    if(type == Type::type_en::exe){
#ifdef Q_OS_LINUX
      qDebug() << "exe running not supported for linux systems";
#elif Q_OS_UNIX
        qDebug() << "exe running not supported for unix systems";
#elif Q_OS_WIN32
        executeProgram(path);
#endif
    }

}

void ExecutionManager::openBrowser(QString link)
{
    QDesktopServices::openUrl(QUrl(link, QUrl::TolerantMode));

}

void ExecutionManager::executeProgram(QString path)
{
    QProcess *proc = new QProcess;

    proc->start(path);

}
