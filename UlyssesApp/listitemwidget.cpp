#include "listitemwidget.h"
#include "ui_listitemwidget.h"

ListItemWidget::ListItemWidget(QWidget *parent, Event *event) :
    QWidget(parent),
    ui(new Ui::ListItemWidget)
{
    ui->setupUi(this);
    ui->timelabel->setText(event->time());
    ui->namelabel->setText(event->name());

    QString type = (event->type() == Type::type::link) ? "link" : "exe";
    ui->typelabel->setText(type);

    QString dayStr = "";
    for(Qt::DayOfWeek day : event->days()){
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
