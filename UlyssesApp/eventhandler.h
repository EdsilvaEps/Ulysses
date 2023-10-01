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
    bool writeEvent(Event ev); // writes an event object into the memory (json file)
    QList<Event> getEvents(); // returns a list of event objects
    bool updateEvent(Event ev, int id); // updates an event in memory based on its ID
    bool removeEvent(int id); // removes event from memory
};

#endif // EVENTHANDLER_H
