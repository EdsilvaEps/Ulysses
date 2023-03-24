#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include "event.h"
#include <QFile>

/*
 * CRUD handler for events
 * TODO: move all related function to here
 * TODO: create signals to communicate the methods' outcome
*/

class EventHandler : public QObject
{
    Q_OBJECT

private:
    QString eventsFile;
    QJsonArray *getEventsJsonArray();
    void writeEventsToFile(QJsonArray array);

public:
    EventHandler(QString events_file);
    bool writeEvent(Event ev);
    QList<Event> getEvents();
    Event *getEvent(int eventId);
    bool updateEvent(int id, Event ev);
    bool removeEvent(int id);
};

#endif // EVENTHANDLER_H
