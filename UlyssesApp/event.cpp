#include "event.h"


const QString &Event::name() const
{
    return _name;
}

void Event::setName(const QString &newName)
{
    _name = newName;
}

const QStringList &Event::args() const
{
    return _args;
}

void Event::setArgs(const QStringList &newArgs)
{
    _args = newArgs;
}

const StartupMode &Event::mode() const
{
    return _mode;
}

void Event::setStartupMode(const StartupMode &mode)
{
    _mode = mode;
}

void Event::setId(int newId)
{
    _id = newId;
}

Event::Event():
    _id(-1), _name("event"), _path(""), _type(Type::type_en::exe), _time("00:00"), _days(QList<Qt::DayOfWeek>())
{
    this->_mode = StartupMode();
}

Event::Event(int id, QString path, Type type, QString time, QList<Qt::DayOfWeek> days)
{
    this->_id = id;
    this->_path = path;
    this->_type = type;
    this->_time = time;
    this->_days = days;
    this->_mode = StartupMode();

    qDebug() << "event created " << id;

    //TODO: prevent wrong types here

}


const QString &Event::path() const
{
    return _path;
}

void Event::setPath(const QString &newPath)
{
    _path = newPath;
}

const Type &Event::type() const
{
    return _type;
}

void Event::setType(const Type &newType)
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

const int &Event::id() const
{
    return _id;
}

QJsonObject Event::getAsJsonObj(){
    QJsonObject eventObj;
    eventObj.insert("id", this->_id);
    eventObj.insert("name", this->_name);
    eventObj.insert("type", this->_type.toString());
    eventObj.insert("time", this->_time);
    eventObj.insert("path", this->_path);
    eventObj.insert("startupmode", this->_mode.toString());

    QJsonArray daysObj = {};
    for(Qt::DayOfWeek day : this->_days){
        if(day == Qt::Monday) daysObj.push_back("Monday");
        if(day == Qt::Tuesday) daysObj.push_back("Tuesday");
        if(day == Qt::Wednesday) daysObj.push_back("Wednesday");
        if(day == Qt::Thursday) daysObj.push_back("Thursday");
        if(day == Qt::Friday) daysObj.push_back("Friday");
        if(day == Qt::Saturday) daysObj.push_back("Saturday");
        if(day == Qt::Sunday) daysObj.push_back("Sunday");
    }
    eventObj.insert("days", daysObj);

    QJsonArray argsObj;
    if(_args.length() > 0){
        for(const QString &argument : _args)
            argsObj.push_back(argument);
    }
    eventObj.insert("args", argsObj);

    return eventObj;

}


