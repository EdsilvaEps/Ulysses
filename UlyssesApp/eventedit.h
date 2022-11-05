#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <fstream>
#include "event.h"

namespace Ui {
class Dialog;
}

class EventEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EventEdit(QWidget *parent = nullptr);
    ~EventEdit();

private slots:


    void on_submitBox_clicked(QAbstractButton *button);

    void on_browseBtn_clicked();

    void on_linkTypeSelection_toggled(bool checked);

    void on_exeTypeSelection_toggled(bool checked);

private:
    Ui::Dialog *ui;
    Event *event;
    bool _isNewEvent; // variable provide from parent
    QString _saveFile;


    void saveEvent();
    void loadEvent();
    void modifyEvent(); // TODO: specify arg details of event
    QList<Qt::DayOfWeek> getSelectedDays();
    bool fieldsValid();
    void writeFormattedEventToFile();
};

#endif // EVENTEDIT_H
