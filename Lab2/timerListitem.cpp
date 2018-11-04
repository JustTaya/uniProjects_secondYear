#include "timerListitem.h"
#include "ui_timerscrollitem.h"

TimerScrollItem::TimerScrollItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerScrollItem)
{
    ui->setupUi(this);
}

TimerScrollItem::~TimerScrollItem()
{
    delete ui;
}

void TimerScrollItem::changeEvent(QEvent *e)
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
