#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QDialog>
#include <QAbstractButton>

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

private:
    Ui::Dialog *ui;

    QString eventPath;
    bool isNewEvent;

    void saveEvent();
    void loadEvent();
    void modifyEvent(); // TODO: specify arg details of event

};

#endif // EVENTEDIT_H
