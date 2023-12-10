#ifndef EVENT_H
#define EVENT_H

//#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "type.h"
#include "startupmode.h"

class Event
{
private:
    int _id;
    QString _name;
    QString _path;
    Type _type;
    StartupMode _mode;
    QString _time;
    QList<Qt::DayOfWeek> _days;
    QStringList _args; // arguments that go along running of scripts

public:

    Event(int id, QString path, Type type, QString time, QList<Qt::DayOfWeek> days);

    Event();

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

    const QStringList &args() const;
    void setArgs(const QStringList &newArgs);

    const StartupMode &mode() const;
    void setStartupMode (const StartupMode &mode);

    QJsonObject getAsJsonObj();

    const int &id() const;
    void setId(int newId);

};

#endif // EVENT_H
