#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "event.h"

namespace Ui {
class Dialog;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EventEdit(QWidget *parent = nullptr);
    ~EventEdit();

    static void removeEvent(int id); // TODO: finish this function -> it should be possible to remove an event from the main list screen

    QJsonArray *getEventsJsonArray(); // returns events as a json array

    QList<Event> *getEvents(); // get all the registered events in a nice list of Event objects

    const QString eventsFile = "/home/edson/Documents/ulysses_conf/testfile.json";

private slots:


    void on_submitBox_clicked(QAbstractButton *button);

    void on_browseBtn_clicked();

    void on_linkTypeSelection_toggled(bool checked);

    void on_exeTypeSelection_toggled(bool checked);

private:
    Ui::Dialog *ui;
    Event *event;
    bool _isNewEvent; // variable provide from parent

    void saveEvent();
    void loadEvent();
    void modifyEvent(); // TODO: specify arg details of event
    QList<Qt::DayOfWeek> getSelectedDays();
    bool fieldsValid();
    void writeFormattedEventToFile();
    int getNextValidId(); // TODO: Finish this function -> it checks whats the next id available for event
    bool isFileEmpty();
};

#endif // EVENTEDIT_H
