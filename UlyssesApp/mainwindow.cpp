#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->time = new QDateTime();
    this->updateVisualDate();
    this->populateList();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addEventBtn_clicked()
{
    // open event creation dialog
    EventEdit * dialog = new EventEdit(this);
    connect(dialog, &EventEdit::accepted, [=]() {
        this->updateList();
    });
    dialog->exec();

}

QList<Event> MainWindow::getEvents()
{
    QList<Event> eventsList;
    QJsonArray *eventsInJson;
    try {
     eventsInJson = EventEdit::getEventsJsonArray(); // TODO: replace this with EventHandler's call of same name
    } catch (std::runtime_error const& e) {
        qDebug() << "config file does not exist, creating...";
        EventEdit::createEmptyConfFile();

    }

    if(!eventsInJson->empty()){
        qDebug() << "getEvents()::Processing list of events...";
        for(const QJsonValue& eventJson : *eventsInJson){
            QJsonObject obj = eventJson.toObject();
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

           Event ev = Event(id, path, type, time, days);
           ev.setName(name);
           ev.setArgs(argsList);
           ev.setStartupMode(mode);
           eventsList.append(ev);
        }
    }
    delete(eventsInJson);
    return eventsList;


}

void MainWindow::populateList()
{
    QList<Event> events = this->getEvents();

    qDebug() << "Number of events to populate: " << events.size();

    try {
        for(Event event : events){
            QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
            ui->listWidget->addItem(listWidgetItem);
            ListItemWidget *customWidgetItem = new ListItemWidget(ui->listWidget,&event);
            listWidgetItem->setSizeHint(customWidgetItem->sizeHint());
            ui->listWidget->setItemWidget(listWidgetItem, customWidgetItem);

            connect(customWidgetItem, &ListItemWidget::eventsChanged, this, &MainWindow::on_eventsUpdated);

            // if this is the first element, then select it
            if(ui->listWidget->count() == 1) ui->listWidget->setCurrentItem(listWidgetItem);
        }
    } catch (std::exception const& e) {
        qDebug() << "mainwindow: " << e.what();
    }


}

void MainWindow::updateList()
{
    ui->listWidget->clear();
    this->populateList();

}

void MainWindow::updateVisualDate()
{
    QLocale::setDefault(QLocale("en_US"));
    ui->date->setText( QLocale().toString( QDate::currentDate() ));

}


void MainWindow::on_removeEventBtn_clicked()
{
    //QString eventsFile = "/home/edson/Documents/ulysses_conf/testfile.json"; // TODO: put this properly somewhere
    //int id = ui->listWidget->currentItem()->
    //ui->listWidget->currentItem();
    //EventHandler evHandler = EventHandler(eventsFile);

}

void MainWindow::on_eventsUpdated()
{
    this->updateList();
}

