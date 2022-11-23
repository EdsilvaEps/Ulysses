#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "type.h"

class Event : public QObject
{
    Q_OBJECT
private:
    int _id;
    QString _name;
    QString _path;
    Type::type _type;
    QString _time;
    QList<Qt::DayOfWeek> _days;

public:
    explicit Event(QObject *parent = nullptr);

    Event(int id, QString path, Type::type type, QString time, QList<Qt::DayOfWeek> days);

    //Event();

    // launch event
    void launch();

    // check if event is within launching time
    bool launchTime();

    const QString &path() const;
    void setPath(const QString &newPath);

    const Type::type &type() const;
    void setType(const Type::type &newType);

    const QString &time() const;
    void setTime(const QString &newTime);

    const QList<Qt::DayOfWeek> &days() const;
    void setDays(const QList<Qt::DayOfWeek> &newDays);

    const QString &name() const;
    void setName(const QString &newName);

    QJsonObject getAsJsonObj();
    void setId(int newId);

signals:

};

#endif // EVENT_H
