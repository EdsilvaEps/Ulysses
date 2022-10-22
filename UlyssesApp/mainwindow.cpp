#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->time = new QDateTime();
    //this->time->currentDateTime().date().dayOfWeek();
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

