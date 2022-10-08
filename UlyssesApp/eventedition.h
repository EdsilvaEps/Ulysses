#ifndef EVENTEDITION_H
#define EVENTEDITION_H

#include <QWidget>

namespace Ui {
class EventEdition;
}

class EventEdition : public QWidget
{
    Q_OBJECT

public:
    explicit EventEdition(QWidget *parent = nullptr);
    ~EventEdition();

private:
    Ui::EventEdition *ui;
};

#endif // EVENTEDITION_H
