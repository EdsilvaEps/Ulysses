#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "event.h"
#include "eventhandler.h"

namespace Ui {
class Dialog;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EventEdit(QWidget *parent = nullptr, int eventID = -1);
    ~EventEdit();

    static QJsonArray *getEventsJsonArray(); // returns events as a json array

    static const inline QString eventsFilePath = "/home/edson/Documents/ulysses_conf/";

    static const inline QString eventsFileName = "testfile.json";

    static const inline QString eventsFile = eventsFilePath + eventsFileName;

    static void createEmptyConfFile(); // creates the empty conf file at the location determined by "eventsFile" property

private slots:

    void on_submitBox_clicked(QAbstractButton *button);

    void on_browseBtn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
    Event *event;
    EventHandler *evHandler;
    bool _isNewEvent; // variable provide from parent
    QStringList _eventTypes = {"link","exe","script"};

    void saveEvent();
    void loadEvent();
    void modifyEvent(); // TODO: specify arg details of event
    QList<Qt::DayOfWeek> getSelectedDays();
    bool fieldsValid();
    void writeFormattedEventToFile();
    int getNextValidId();
    bool isFileEmpty();
    void selectCurrentEventData(); // select the user input data and put on the event object, ready for saving
};


#endif // EVENTEDIT_H
