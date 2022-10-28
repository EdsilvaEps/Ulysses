#include "eventedit.h"
#include "ui_eventedit.h"
#include "QMessageBox"
#include <QFileDialog>

EventEdit::EventEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->isNewEvent = true; // TODO: condition for setting this boolean
    this->event = new Event();
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
        return;
    }

    // theres no need to add if condition for ok button clicked
    int ret = QMessageBox::question(this, confirmTitle, confirmText,
                                    QMessageBox::Ok | QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel){
        reject();
        return;
    }

    if(ret == QMessageBox::Ok){
        if(this->isNewEvent){

            this->saveEvent();
        } else this->modifyEvent();
        accept();
    }

}


void EventEdit::on_browseBtn_clicked()
{
    // open the file explorer
    QString executable;
    QFileDialog fileDiag;
    fileDiag.setOption(QFileDialog::DontUseNativeDialog, true);
    fileDiag.setFilter(QDir::Executable | QDir::Files);
    QFileDialog::getOpenFileName(this, tr("Select Executable"), executable);

    if(!executable.isNull()){
        this->event->setPath(executable);
        ui->urlPath->setText(executable);

    }

}

void EventEdit::saveEvent()
{
    qDebug() << "saving event...";

}

void EventEdit::loadEvent()
{
    qDebug() << "loading event...";

}

void EventEdit::modifyEvent()
{
    qDebug() << "Modifying event...";
}



void EventEdit::on_linkTypeSelection_toggled(bool checked)
{
    if(checked) ui->browseBtn->setDisabled(true); // disable browse btn if we are using a link
    this->event->setType(Type::link);

}


void EventEdit::on_exeTypeSelection_toggled(bool checked)
{
    if(checked) ui->browseBtn->setDisabled(false);
    this->event->setType(Type::exe);
}

