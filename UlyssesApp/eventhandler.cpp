#include "eventhandler.h"

EventHandler::EventHandler(QString events_file)
{
    this->eventsFile = events_file;

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
    if (file.open(QIODevice::ReadWrite)) {
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
        qDebug() << "verifying obj " << objId;

        if(id == objId){
            eventsInJson->removeAt(i);
            removed = true;
            break;
        }

    }
    this->writeEventsToFile(*eventsInJson);

    return removed;


}


