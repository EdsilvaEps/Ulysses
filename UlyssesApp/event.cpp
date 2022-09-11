#include "event.h"

Event::Event(QObject *parent)
    : QObject{parent}
{

}

Event::Event(int id, QString path, Type::type type, QTime *time, QList<Qt::DayOfWeek> days)
{
    this->_id = id;
    this->_path = path;
    this->_type = type;
    this->_time = time;
    this->_days = days;

    //TODO: prevent wrong types here
    //TODO: also processing paths is gonna be necessary

}

void Event::launch()
{
    if(this->_type == Type::type::link){
        QDesktopServices::openUrl(QUrl(this->_path, QUrl::TolerantMode));
        // add helper to tell if the link cannot be opened
    }

    if(this->_type == Type::type::exe){
        QProcess *process = new QProcess(this);
        process->start(this->_path);
    }

}

bool Event::launchTime()
{
    QDateTime *now = new QDateTime;
    *now = QDateTime::currentDateTime();

    if(this->_days.contains(now->date().dayOfWeek())){
        if(this->_time->hour()==now->time().hour()){
            return true;
        }
    }
    return false;

}


