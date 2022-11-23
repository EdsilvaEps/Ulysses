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

    // ------------- TODO: everything below should have its own class (adapter) -------------------
    // ------------------- create a mock element on the list --------------------------------------
    // creating new generic list item
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);

    // adding item to list widget
    ui->listWidget->addItem(listWidgetItem);

    // creating an object of our custom list item widget
    ListItemWidget *testItemWidgetItem = new ListItemWidget;

    // making sure that the generic list item is the same size as the custom item widget
    listWidgetItem->setSizeHint(testItemWidgetItem->sizeHint());

    // finally, adding the item widget to the list
    ui->listWidget->setItemWidget(listWidgetItem, testItemWidgetItem);


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

void MainWindow::populateList(QString sourcePath)
{

}

