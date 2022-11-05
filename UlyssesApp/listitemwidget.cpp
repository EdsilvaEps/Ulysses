#include "listitemwidget.h"
#include "ui_listitemwidget.h"

ListItemWidget::ListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemWidget)
{
    ui->setupUi(this);
}

ListItemWidget::~ListItemWidget()
{
    delete ui;
}
