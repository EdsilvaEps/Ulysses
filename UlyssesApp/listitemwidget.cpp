#include "listitemwidget.h"
#include "ui_listitemwidget.h"
#include "eventhandler.h"

ListItemWidget::ListItemWidget(QWidget *parent, Event *event) :
    QWidget(parent),
    ui(new Ui::ListItemWidget)
{
    this->event = *event;
    ui->setupUi(this);
    ui->timelabel->setText(this->event.time());
    ui->namelabel->setText(this->event.name());

    QString type = (this->event.type() == Type::type_en::link) ? "link" : "exe";
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

void ListItemWidget::on_toolButton_clicked()
{
    ExecutionManager::run(this->event.path(), this->event.type());
}

void ListItemWidget::on_settingsbtn_clicked()
{
    // open event creation dialog with parameter for event edition
    qDebug() << "Editting event";
    EventEdit * dialog = new EventEdit(this, this->event.id());
    connect(dialog, &EventEdit::accepted, [=]() {
        emit eventsChanged();
    });
    dialog->exec();
}

