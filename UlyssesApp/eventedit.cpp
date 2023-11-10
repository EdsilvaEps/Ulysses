#include "eventedit.h"
#include "ui_eventedit.h"
#include "QMessageBox"
#include <QFileDialog>
#include "event.h"

EventEdit::EventEdit(QWidget *parent, int eventID) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    evHandler = new EventHandler(this->eventsFile);

    // in case of no valid eventID supplied
    if(eventID < 0){
        this->_isNewEvent = true;
        this->event = new Event();
        this->event->setType(Type::link);
        ui->linkTypeSelection->setChecked(true);
        ui->browseBtn->setDisabled(true);


    } else{ // set the event edit screen with the data of the selected event

        this->_isNewEvent = false;
        this->event = evHandler->getEvent(eventID);
        qDebug() << "editting event: " << this->event->name();

        ui->eventName->setText(this->event->name());
        if(this->event->type() == Type::type_en::link){
            ui->linkTypeSelection->setChecked(true);
            ui->browseBtn->setDisabled(true);
        } else{
            ui->exeTypeSelection->setChecked(true);
            ui->browseBtn->setDisabled(false);
        }

        ui->urlPath->setText(this->event->path());
        ui->timeEdit->setTime(QDateTime::fromString(this->event->time(),"HH:mm").time());

        for(Qt::DayOfWeek day: this->event->days()){
            if(day == Qt::DayOfWeek::Monday) ui->monSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Tuesday) ui->tueSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Wednesday) ui->wedSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Thursday) ui->thuSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Friday) ui->friSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Saturday) ui->satSelection->setCheckState(Qt::Checked);
            if(day == Qt::DayOfWeek::Sunday) ui->sunSelection->setCheckState(Qt::Checked);
        }

    }

}

EventEdit::~EventEdit()
{
    delete ui;
}

QJsonArray *EventEdit::getEventsJsonArray()
{
    QJsonArray *events = new QJsonArray;

    QString val;
    QFile file(EventEdit::eventsFile);
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

void EventEdit::on_submitBox_clicked(QAbstractButton *button)
{
    if(!fieldsValid()) return;

    QDialogButtonBox::StandardButton stdButton = ui->submitBox->standardButton(button);
    QString confirmTitle = "Edit Event";
    QString confirmText = "Are you sure you want to modify the event?";
    if(this->_isNewEvent){
        confirmTitle = "Save Event";
        confirmText = "Are you sure you want to save the event?";

    }

    if(stdButton == QDialogButtonBox::Cancel){
        reject();
        return;
    }

    // theres no need to add if condition for ok button clicked
    int ret = QMessageBox::question(this, confirmTitle, confirmText,
                                    QMessageBox::Ok | QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel){
        reject();
        return;
    }

    if(ret == QMessageBox::Ok){
        if(this->_isNewEvent){
            this->saveEvent();
        } else this->modifyEvent();
        accept();
    }

}


void EventEdit::on_browseBtn_clicked()
{
    // open the file explorer
    QString executable;
    QFileDialog fileDiag;
    fileDiag.setOption(QFileDialog::DontUseNativeDialog, true);
    fileDiag.setFilter(QDir::Executable | QDir::Files);
    QFileDialog::getOpenFileName(this, tr("Select Executable"), executable);

    if(!executable.isNull()){
        this->event->setPath(executable);
        ui->urlPath->setText(executable);

    }

}


QList<Qt::DayOfWeek> EventEdit::getSelectedDays(){
    QList<Qt::DayOfWeek> selectedDays;
    if(ui->monSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Monday);
    if(ui->tueSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Tuesday);
    if(ui->wedSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Wednesday);
    if(ui->thuSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Thursday);
    if(ui->friSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Friday);
    if(ui->satSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Saturday);
    if(ui->sunSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Sunday);

    return selectedDays;

}

bool EventEdit::fieldsValid(){
    if(ui->urlPath->text().isEmpty()){
        QMessageBox::warning(this, "Missing field", "Link or path to executable is missing");
        return false;
    }

    QList<Qt::DayOfWeek> list = getSelectedDays();
    if(list.empty()){
        QMessageBox::warning(this, "Missing field", "You have to select at least one day for the event");
        return false;
    }

    return true;

}

void EventEdit::writeFormattedEventToFile()
{
    qDebug() << "saving event to file..." + this->eventsFile;
    QJsonDocument doc(this->event->getAsJsonObj());
    QString strEvent(doc.toJson());

    QString filename = this->eventsFile;
    QFile file(filename);
    if(this->isFileEmpty()){
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);

            stream << "[" << Qt::endl;
            stream << strEvent << Qt::endl;
            stream << "]";
            file.close();
        }
        else throw std::runtime_error("could not open file");
        return;
    }

    QJsonArray *events;
    try {
        events = this->getEventsJsonArray();
    } catch (std::runtime_error const& e) {
        qDebug() << "configuration file does not exist, creating...";
        this->createEmptyConfFile();
        events = this->getEventsJsonArray();
    }

    events->push_back(this->event->getAsJsonObj());
    QJsonDocument eventsDoc(*events);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);

        stream << QString(eventsDoc.toJson()) << Qt::endl;
        file.close();
    }
    else throw std::runtime_error("could not open file");
    return;
}

int EventEdit::getNextValidId()
{
    if(this->isFileEmpty()) return 0;
    return this->getEventsJsonArray()->size();
}

Event *EventEdit::getEventData(){
    Event *ev = new Event();
    ev->setId(this->event->id());
    if(this->_isNewEvent)
        ev->setId(this->getNextValidId());
    ev->setPath(ui->urlPath->text());
    ev->setDays(getSelectedDays());
    ev->setTime(ui->timeEdit->text());
    QString eventName = (ui->eventName->text().isEmpty()) ? "event" : ui->eventName->text();
    ev->setName(eventName);

    return ev;
}

void EventEdit::saveEvent()
{
    this->event = this->getEventData();
    qDebug() << "saving event...";
    writeFormattedEventToFile();

}

void EventEdit::loadEvent()
{
    qDebug() << "loading event...";

}

void EventEdit::modifyEvent()
{
    qDebug() << "Modifying event...";
    this->event = this->getEventData();
    if(evHandler->updateEvent(this->event->id(), *this->event)){
        qDebug() << "event successfully modified";
        return;
    }
    qDebug() << "failed to modify event";

}

bool EventEdit::isFileEmpty(){

    QString filename = this->eventsFile;
    QFile file(filename);
    if(file.size() > 0) return false;
    return true;
}

void EventEdit::createEmptyConfFile()
{

    QDir *dir = new QDir();
    if(dir->mkpath(EventEdit::eventsFilePath)){
        qDebug() << "path to file created";
        QString filename = EventEdit::eventsFile;
        QFile file(filename);
        file.open(QIODevice::ReadWrite);
        file.close();
        return;
    }

    qDebug() << "could not create file path";

}


void EventEdit::on_linkTypeSelection_toggled(bool checked)
{
    if(checked) ui->browseBtn->setDisabled(true); // disable browse btn if we are using a link
    this->event->setType(Type::link);

}


void EventEdit::on_exeTypeSelection_toggled(bool checked)
{
    if(checked) ui->browseBtn->setDisabled(false);
    this->event->setType(Type::exe);
}

