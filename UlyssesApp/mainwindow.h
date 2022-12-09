#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QListWidgetItem>
#include "listitemwidget.h"
#include "eventedit.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addEventBtn_clicked();

private:
    Ui::MainWindow *ui;
    QDateTime *time;

    void populateList(); // gets the file where events are written and loads them into the UI list
    void updateList();
    QList<Event> getEvents();
};
#endif // MAINWINDOW_H
