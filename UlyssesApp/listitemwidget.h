#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ListItemWidget;
}

class ListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemWidget(QWidget *parent = nullptr);
    ~ListItemWidget();

private:
    Ui::ListItemWidget *ui;
};

#endif // LISTITEMWIDGET_H
