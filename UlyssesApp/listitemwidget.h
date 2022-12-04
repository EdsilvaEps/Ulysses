#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
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

private:
    Ui::ListItemWidget *ui;
    Event *event; // object that constitutes the data of this element
};

#endif // LISTITEMWIDGET_H
