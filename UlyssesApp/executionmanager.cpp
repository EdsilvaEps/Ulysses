#include "executionmanager.h"
#include <memory>
#include <QDebug>

ExecutionManager::ExecutionManager()
{
    proc = new QProcess; // initialize QProcess obj
    connect(proc, &QProcess::errorOccurred, this, &ExecutionManager::onErrorOccurred);
    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &ExecutionManager::onRunFinished);
    connect(proc, &QProcess::started, this, &ExecutionManager::onProgramStarted);


}

ExecutionManager::~ExecutionManager()
{
    delete proc;
}

void ExecutionManager::run(QString path, Type type, QStringList args)
{
    if(type == Type::type_en::link){
        openBrowser(path);
    }

    if(type == Type::type_en::exe){
#ifdef Q_OS_LINUX
      qDebug() << "exe running not supported for linux systems";
      emit runErrorOccurred("exe running not supported for linux systems");
#elif Q_OS_UNIX
        qDebug() << "exe running not supported for unix systems";
        emit runErrorOccurred("exe running not supported for linux systems");
#elif Q_OS_WIN32
        executeProgram(path);
#endif
    }

    if(type == Type::type_en::script_shell){
#ifdef Q_OS_WIN32
        emit runErrorOccurred("bash script running not supported for windows systems");
        return;
#endif
       runScript(path, type, args);
    }

    if(type == Type::type_en::script_python)
    {
        runScript(path, type, args);
    }


}

void ExecutionManager::onErrorOccurred(QProcess::ProcessError error)
{
    QString errMsg = "";
    if(error == QProcess::FailedToStart) errMsg = "Couldn't start process";
    if(error == QProcess::Crashed) errMsg = "Process crashed";
    if(error == QProcess::Timedout) errMsg = "Process Timeout";
    if(error == QProcess::WriteError) errMsg = "Couldn't write process";
    if(error == QProcess::ReadError) errMsg = "Could not read from process";
    if(error == QProcess::UnknownError) errMsg = "Process failed: unknown error";
    emit runErrorOccurred(errMsg);

}

void ExecutionManager::onRunFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    bool success = false;
    QString exitMsg = "";
    if(exitStatus == QProcess::NormalExit){
       success = true;
       exitMsg = &"Process succefully ended with status " [ exitCode];
    }
    else
        exitMsg = &"Process failed with status " [ exitCode];

    emit runFinished(success, exitMsg);

}

void ExecutionManager::onProgramStarted()
{
    emit processStarted();
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

void ExecutionManager::runScript(QString path, Type type, QStringList args)
{
    QStringList input {path};
    if(args.length() > 0 ){
        input.append(args);
        qDebug() << "running script with " << args.length() << " args";
    }
    if(type == Type::type_en::script_python)
        proc->start("python3", input);
    if(type == Type::type_en::script_shell)
        proc->start("/bin/bash", input);
    // TODO: something will have to be done about the program arg here, it's gonna be different in each system
    // maybe add some config for it

}
