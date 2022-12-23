#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "event.h"

namespace Ui {
class ListItemWidget;
}

class ListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemWidget(QWidget *parent = nullptr, Event *event = new Event());
    ~ListItemWidget();

signals:
    void eventsChanged();

private slots:
    void on_removeItem_clicked();


private:
    Ui::ListItemWidget *ui;
    Event event; // object that constitutes the data of this element
};

#endif // LISTITEMWIDGET_H
