#include "listitemwidget.h"
#include "ui_listitemwidget.h"
#include "eventhandler.h"

ListItemWidget::ListItemWidget(QWidget *parent, Event *event) :
    QWidget(parent),
    ui(new Ui::ListItemWidget)
{
    this->event = *event;
    qDebug() << "getting ahold of event " << this->event.id();
    ui->setupUi(this);
    ui->timelabel->setText(this->event.time());
    ui->namelabel->setText(this->event.name());

    QString type = (this->event.type() == Type::type::link) ? "link" : "exe";
    ui->typelabel->setText(type);

    QString dayStr = "";
    for(Qt::DayOfWeek day : this->event.days()){
        if(day == Qt::Monday) dayStr += "Mon ";
        if(day == Qt::Tuesday) dayStr += "Tue ";
        if(day == Qt::Wednesday) dayStr += "Wed ";
        if(day == Qt::Thursday) dayStr += "Thu ";
        if(day == Qt::Friday) dayStr += "Fri ";
        if(day == Qt::Saturday) dayStr += "Sat ";
        if(day == Qt::Sunday) dayStr += "Sun ";
    }
    ui->dayslabel->setText(dayStr);


}

ListItemWidget::~ListItemWidget()
{
    delete ui;
}

void ListItemWidget::on_removeItem_clicked()
{
    qDebug() << "deleting event";
    qDebug() << "removing event "  << this->event.id();
    QString eventsFile = "/home/edson/Documents/ulysses_conf/testfile.json"; // TODO: put this properly somewhere
    EventHandler evHandler = EventHandler(eventsFile);
    try {
        evHandler.removeEvent(event.id());
        emit eventsChanged();
    } catch (...) {
        // TODO: add error catching here
    }




}
