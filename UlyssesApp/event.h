#ifndef EVENT_H
#define EVENT_H

//#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "type.h"

class Event
{
private:
    int _id;
    QString _name;
    QString _path;
    Type _type;
    QString _time;
    QList<Qt::DayOfWeek> _days;

public:
    //explicit Event(QObject *parent = nullptr);

    Event(int id, QString path, Type type, QString time, QList<Qt::DayOfWeek> days);

    Event();

    // launch event
    //void launch();

    // check if event is within launching time
    bool launchTime();

    const QString &path() const;
    void setPath(const QString &newPath);

    const Type &type() const;
    void setType(const Type &newType);

    const QString &time() const;
    void setTime(const QString &newTime);

    const QList<Qt::DayOfWeek> &days() const;
    void setDays(const QList<Qt::DayOfWeek> &newDays);

    const QString &name() const;
    void setName(const QString &newName);

    QJsonObject getAsJsonObj();

    const int &id() const;
    void setId(int newId);

};

#endif // EVENT_H
