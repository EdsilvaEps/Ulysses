#include "event.h"

/*#include <sstream>
#include <chrono>
#include <iomanip>

using std::chrono::system_clock;

namespace {
    system_clock::time_point getTimePoint(QString time) {
        std::tm myTm = {};
        std::stringstream ss(time.toStdString().c_str());
        ss >> std::get_time(&myTm, "%H:%M");
        return system_clock::from_time_t(std::mktime(&myTm));

    }
} */


Event::Event(QObject *parent) : QObject{parent},
    _id(-1), _path(""), _type(Type::link), _time("00:00"), _days(QList<Qt::DayOfWeek>())
{

}

Event::Event(int id, QString path, Type::type type, QString time, QList<Qt::DayOfWeek> days)
{
    this->_id = id;
    this->_path = path;
    this->_type = type;
    this->_time = time;
    this->_days = days;

    //TODO: prevent wrong types here
    //TODO: also processing paths is gonna be necessary

}


const QString &Event::path() const
{
    return _path;
}

void Event::setPath(const QString &newPath)
{
    _path = newPath;
}

const Type::type &Event::type() const
{
    return _type;
}

void Event::setType(const Type::type &newType)
{
    _type = newType;
}

const QString &Event::time() const
{
    return _time;
}

void Event::setTime(const QString &newTime)
{
    _time = newTime;
}

const QList<Qt::DayOfWeek> &Event::days() const
{
    return _days;
}

void Event::setDays(const QList<Qt::DayOfWeek> &newDays)
{
    _days = newDays;
}

void Event::launch()
{
    // TODO: this all should be handled by a daemon
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
    //QDateTime *now = new QDateTime;
    //*now = QDateTime::currentDateTime();

    //if(this->_days.contains(now->date().dayOfWeek())){
    //    if(this->_time->hour()==now->time().hour()){
    //        return true;
    //    }
    //}
    //return false;
    return false;

}


