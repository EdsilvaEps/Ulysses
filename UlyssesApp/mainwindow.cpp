#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_listitemwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->time = new QDateTime();
    //this->time->currentDateTime().date().dayOfWeek();

    // creating new generic list item
    //QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);

    // adding item to list widget
    //ui->listWidget->addItem(listWidgetItem);

    // creating an object of our custom list item widget
    //ListItemWidget *testItemWidgetItem = new ListItemWidget;

    // making sure that the generic list item is the same size as the custom item widget
    //listWidgetItem->setSizeHint(testItemWidgetItem->sizeHint());

    // finally, adding the item widget to the list
    //ui->listWidget->setItemWidget(listWidgetItem, testItemWidgetItem);

    QList<Event> events = this->getEvents();
    qDebug() << "Number of events to populate: " << events.size();

    for(Event event : events){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(listWidgetItem);
        ListItemWidget *customWidgetItem = new ListItemWidget(ui->listWidget,&event);
        listWidgetItem->setSizeHint(customWidgetItem->sizeHint());
        ui->listWidget->setItemWidget(listWidgetItem, customWidgetItem);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addEventBtn_clicked()
{
    // open event creation dialog
    EventEdit * dialog = new EventEdit(this);
    dialog->exec();

}

QList<Event> MainWindow::getEvents()
{
    QList<Event> eventsList;
    QJsonArray *eventsInJson;
    eventsInJson = EventEdit::getEventsJsonArray();

    if(!eventsInJson->empty()){
        qDebug() << "getEvents()::Processing list of events...";
        for(const QJsonValue& eventJson : *eventsInJson){
            QJsonObject obj = eventJson.toObject();
            int id = obj["id"].toInt();
            QString name = obj["name"].toString();
            QString path = obj["path"].toString();
            QString time = obj["time"].toString();
            Type::type type = (obj["type"].toString() == "link") ? Type::link : Type::exe;
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

           Event ev = Event(id, path, type, time, days);
           ev.setName(name);
           eventsList.append(ev);
        }
    }
    delete(eventsInJson);
    return eventsList;


}

void MainWindow::populateList(QString sourcePath) // TODO: This should be changed to "updateList" and called after eventedit
{

}



