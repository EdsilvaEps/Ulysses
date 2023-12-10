#include "eventhandler.h"

EventHandler::EventHandler(QString events_file)
{
    this->eventsFile = events_file;

}


Event *EventHandler::getEvent(int eventId){
    QJsonArray *events;
    Event *event = new Event();
    try {
     events = this->getEventsJsonArray();
    } catch (std::runtime_error const& e) {
        qDebug() << "could not open config file" ;
        return NULL;
    }


    for(int i = 0; i < events->count(); i++){
        QJsonValue temp = events->at(i);
        //QJsonObject temp = val.toObject();
        QJsonValue val = temp.toObject().value("id");
        int objId = val.toInt(-1);

        if(eventId == objId){

            QJsonObject obj = temp.toObject();
            int id = obj["id"].toInt();
            QString name = obj["name"].toString();
            QString path = obj["path"].toString();
            QString time = obj["time"].toString();
            Type type = Type::strToTypeEnum(obj["type"].toString());
            StartupMode mode = StartupMode(obj["startupmode"].toString(""));

            QList<Qt::DayOfWeek> days;
            for(int i=0; i< obj["days"].toArray().count(); ++i){
                QString str = obj["days"].toArray().at(i).toString();
                if(str == "Monday") days.append(Qt::Monday);
                if(str == "Tuesday") days.append(Qt::Tuesday);
                if(str == "Wednesday") days.append(Qt::Wednesday);
                if(str == "Thursday") days.append(Qt::Thursday);
                if(str == "Friday") days.append(Qt::Friday);
                if(str == "Saturday") days.append(Qt::Saturday);
                if(str == "Sunday") days.append(Qt::Sunday);
            }

            QStringList argsList;
            for(QJsonValueRef argObj : obj["args"].toArray()){
                argsList.append(argObj.toString(""));
            }

           event->setId(id);
           event->setPath(path);
           event->setType(type);
           event->setTime(time);
           event->setDays(days);
           event->setName(name);
           event->setArgs(argsList);
           event->setStartupMode(mode);
           break;
        }
    }
    return event;

}


bool EventHandler::updateEvent(Event ev, int id)
{
    bool modified = false;
    QJsonArray *eventsInJson;
    eventsInJson = this->getEventsJsonArray();

    for(int i = 0; i < eventsInJson->count(); i++){
        QJsonValue temp = eventsInJson->at(i);
        //QJsonObject temp = val.toObject();
        QJsonValue val = temp.toObject().value("id");
        int objId = val.toInt(-1);

        if(id == objId){
            eventsInJson->replace(i, ev.getAsJsonObj());
            modified = true;
            break;
        }

    }
    this->writeEventsToFile(*eventsInJson);
    return modified;


}

bool EventHandler::updateEvent(int eventToEditID, Event newEvent)
{
    QJsonArray *events;
    try {
     events = this->getEventsJsonArray();
    } catch (std::runtime_error const& e) {
        qDebug() << "could not open config file" ;
        return false;
    }

    for(int i = 0; i < events->count(); i++){
        QJsonValue temp = events->at(i);
        //QJsonObject temp = val.toObject();
        QJsonValue val = temp.toObject().value("id");
        int objId = val.toInt(-1);
        if(eventToEditID == objId){
            events->replace(i, newEvent.getAsJsonObj());
            this->writeEventsToFile(*events);
            return true;
        }

    }
    return false;
}

QJsonArray *EventHandler::getEventsJsonArray()
{
    QJsonArray *events = new QJsonArray;

    QString val;
    QFile file(this->eventsFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        val = file.readAll();
    }
    else throw std::runtime_error("could not open file");
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    if(d.isArray()) *events = d.array();
    qDebug() << d;
    return events;

}

void EventHandler::writeEventsToFile(QJsonArray eventsArray)
{
    QFile file(this->eventsFile);
    QJsonDocument eventsDoc(eventsArray);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream stream(&file);

        stream << QString(eventsDoc.toJson()) << Qt::endl;
        file.close();
    }
    else throw std::runtime_error("could not open file");
    return;

}

bool EventHandler::removeEvent(int id)
{
    bool removed = false;
    QJsonArray *eventsInJson;
    eventsInJson = this->getEventsJsonArray();

    for(int i = 0; i < eventsInJson->count(); i++){
        QJsonValue temp = eventsInJson->at(i);
        //QJsonObject temp = val.toObject();
        QJsonValue val = temp.toObject().value("id");
        int objId = val.toInt(-1);

        if(id == objId){
            eventsInJson->removeAt(i);
            removed = true;
            break;
        }

    }
    this->writeEventsToFile(*eventsInJson);

    return removed;


}



