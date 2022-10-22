#include "eventedit.h"
#include "ui_eventedit.h"
#include "QMessageBox"

EventEdit::EventEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

EventEdit::~EventEdit()
{
    delete ui;
}

void EventEdit::on_submitBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->submitBox->standardButton(button);
    QString confirmTitle = "Edit Event";
    QString confirmText = "Are you sure you want to modify the event?";
    if(this->isNewEvent){
        confirmTitle = "Save Event";
        confirmText = "Are you sure you want to save the event?";

    }

    if(stdButton == QDialogButtonBox::Cancel){
        reject();
        return; // TODO: is this necessary?
    }

    // theres no need to add if condition for ok button clicked
    int ret = QMessageBox::question(this, confirmTitle, confirmText,
                                    QMessageBox::Ok | QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel){
        reject();
        return;
    }

    if(this->isNewEvent){
        this->saveEvent();
    } else this->modifyEvent();

    accept();

}


void EventEdit::on_browseBtn_clicked()
{

}

