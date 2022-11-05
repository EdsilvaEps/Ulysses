#include "eventedit.h"
#include "ui_eventedit.h"
#include "QMessageBox"
#include <QFileDialog>

EventEdit::EventEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->_isNewEvent = true; // TODO: get this as parameters from parent screen
    this->event = new Event();

    ui->linkTypeSelection->setChecked(true);
    ui->browseBtn->setDisabled(true);
    this->event->setType(Type::link);

}

EventEdit::~EventEdit()
{
    delete ui;
}

void EventEdit::on_submitBox_clicked(QAbstractButton *button)
{
    if(!fieldsValid()) return;

    QDialogButtonBox::StandardButton stdButton = ui->submitBox->standardButton(button);
    QString confirmTitle = "Edit Event";
    QString confirmText = "Are you sure you want to modify the event?";
    if(this->_isNewEvent){
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
        if(this->_isNewEvent){

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


QList<Qt::DayOfWeek> EventEdit::getSelectedDays(){
    QList<Qt::DayOfWeek> selectedDays;
    if(ui->monSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Monday);
    if(ui->tueSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Tuesday);
    if(ui->wedSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Wednesday);
    if(ui->thuSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Thursday);
    if(ui->friSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Friday);
    if(ui->satSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Saturday);
    if(ui->sunSelection->isChecked()) selectedDays.append(Qt::DayOfWeek::Sunday);

    return selectedDays;

}

bool EventEdit::fieldsValid(){
    if(ui->urlPath->text().isEmpty()){
        QMessageBox::warning(this, "Missing field", "Link or path to executable is missing");
        return false;
    }

    QList<Qt::DayOfWeek> list = getSelectedDays();
    if(list.empty()){
        QMessageBox::warning(this, "Missing field", "You have to select at least one day for the event");
        return false;
    }

    return true;

}

void EventEdit::writeFormattedEventToFile()
{
    // TODO: add method for reading doc, checking and incrementing ID

    this->_saveFile = "/home/edson/Documents/ulysses_conf/testfile.txt"; // TODO: put this variable in some standard location

    qDebug() << "saving event to file..." + _saveFile;

    // initialize file
    std::ofstream outfile;
    outfile.open(this->_saveFile.toStdString(), std::ios_base::app);

    // continue
    if(outfile.is_open()){
        outfile << this->event->getAsJsonDoc().toJson().toStdString() + ",";
        outfile.close();
    }
    else throw std::runtime_error("could not open file");





}

void EventEdit::saveEvent()
{

    this->event->setPath(ui->urlPath->text());
    this->event->setDays(getSelectedDays());
    this->event->setTime(ui->timeEdit->text());

    qDebug() << "saving event...";
    writeFormattedEventToFile();

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

