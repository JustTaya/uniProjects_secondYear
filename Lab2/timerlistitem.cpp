#include "timerlistitem.h"
#include "ui_timerlistitem.h"

TimerListItem::TimerListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerListItem)
{
    ui->setupUi(this);
}

TimerListItem::~TimerListItem()
{
    delete ui;
}

void TimerListItem::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
