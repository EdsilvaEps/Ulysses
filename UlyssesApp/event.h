#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QDateTime>
#include "type.h"

class Event : public QObject
{
    Q_OBJECT
private:
    int _id;
    QString _path;
    Type::type _type;
    QTime *_time;
    QList<Qt::DayOfWeek> _days;

public:
    explicit Event(QObject *parent = nullptr);

    Event(int id, QString path, Type::type type, QTime *time, QList<Qt::DayOfWeek> days);

    // launch event
    void launch();

    // check if event is within launching time
    bool launchTime();

signals:

};

#endif // EVENT_H
