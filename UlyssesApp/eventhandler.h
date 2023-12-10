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
    QJsonArray *getEventsJsonArray();
    void writeEventsToFile(QJsonArray array);

    QString eventsFilePath = "/home/edson/Documents/ulysses_conf/";

    QString eventsFileName = "testfile.json";

    QString eventsFile = eventsFilePath + eventsFileName;

public:
    EventHandler(QString events_file);
    bool writeEvent(Event ev); // writes an event object into the memory (json file)
    Event *getEvent(int eventId); // gets a single event identified by ID
    bool updateEvent(Event ev, int id); // updates an event in memory based on its ID
    bool updateEvent(int id, Event ev);
    bool removeEvent(int id); // removes event from memory
};

#endif // EVENTHANDLER_H
