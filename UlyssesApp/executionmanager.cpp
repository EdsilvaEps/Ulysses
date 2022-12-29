#include "executionmanager.h"

ExecutionManager::ExecutionManager()
{

}

void ExecutionManager::run(QString path, Type::type type)
{
    if(type == Type::type::link){
        // TODO: do some checking here
        openBrowser(path);
    }

    if(type == Type::type::exe){
        // TODO: do some checking here
        executeProgram(path);
    }

}

void ExecutionManager::openBrowser(QString link)
{

}

void ExecutionManager::executeProgram(QString path)
{

}
