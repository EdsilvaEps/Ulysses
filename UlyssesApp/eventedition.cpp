#include "eventedition.h"
#include "ui_eventedition.h"

EventEdition::EventEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventEdition)
{
    ui->setupUi(this);
}

EventEdition::~EventEdition()
{
    delete ui;
}
