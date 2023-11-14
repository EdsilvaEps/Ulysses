#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include <QObject>
#include "type.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QDebug>


class ExecutionManager : public QObject
{
    Q_OBJECT
public:

    ExecutionManager();
    ~ExecutionManager();

    void run(QString path, Type type);

signals:
    void runErrorOccurred(const QString errMsg);
    void runFinished(bool success, const QString exitStatus);
    void processStarted();
    /*
errorOccurred(QProcess::ProcessError error)
void 	finished(int exitCode, QProcess::ExitStatus exitStatus)*/

private slots:
    void onErrorOccurred(QProcess::ProcessError error);
    void onRunFinished(int exitCode, QProcess::ExitStatus exitStatus); // run button action
    void onProgramStarted();

private:
    QProcess *proc;

    void openBrowser(QString link);
    void executeProgram(QString path);
    void runScript(QString path);
};

#endif // EXECUTIONMANAGER_H
