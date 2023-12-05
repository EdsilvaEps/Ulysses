#include "listitemwidget.h"
#include "qstyle.h"
#include "ui_listitemwidget.h"
#include "eventhandler.h"
#include <memory>

ListItemWidget::ListItemWidget(QWidget *parent, Event *event) :
    QWidget(parent),
    ui(new Ui::ListItemWidget)
{
    this->event = *event;
    ui->setupUi(this);
    ui->timelabel->setText(this->event.time());
    ui->namelabel->setText(this->event.name());

    QString type = this->event.type().toString();
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

    this->execMan = new ExecutionManager();
    connect(execMan, &ExecutionManager::runErrorOccurred, this, &ListItemWidget::programError);
    connect(execMan, &ExecutionManager::runFinished, this, &ListItemWidget::programFinished);
    connect(execMan, &ExecutionManager::processStarted, this, &ListItemWidget::programStarted);

    ui->statusBtn->setVisible(false);

}

ListItemWidget::~ListItemWidget()
{
    delete ui;
    delete execMan;
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
    qDebug() << "run clicked";
    if(this->event.args().length() > 0){
       execMan->run(this->event.path(), this->event.type(), this->event.args());
    }
    else execMan->run(this->event.path(), this->event.type(), {""});
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

void ListItemWidget::programError(const QString errMsg)
{
    qDebug() << errMsg;
    setEventStatus("failure", errMsg);


}

void ListItemWidget::programStarted()
{
    qDebug() << "Program started";
    setEventStatus("started", "Program started");
}

void ListItemWidget::programFinished(bool success, const QString exitStatus)
{
    if(success){
        qDebug() << exitStatus;
        setEventStatus("success", exitStatus);
    } else setEventStatus("failure", exitStatus);


}

void ListItemWidget::setEventStatus(const QString status, const QString tooltip)
{
    QStyle *style = QApplication::style();
    QIcon myIcon;
    if(status == "success") myIcon = style->standardIcon(QStyle::SP_DialogOkButton);
    if(status == "failure") myIcon = style->standardIcon(QStyle::SP_DialogCancelButton);
    if(status == "started") myIcon = style->standardIcon(QStyle::SP_MediaPlay);
    ui->statusBtn->setIcon(myIcon);
    ui->statusBtn->setVisible(true);
    ui->statusBtn->setToolTip(tooltip);

}

