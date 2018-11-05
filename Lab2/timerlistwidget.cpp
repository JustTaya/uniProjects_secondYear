#include "timerlistwidget.h"
#include "ui_timerlistwidget.h"

TimerListWidget::TimerListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerListWidget)
{
    ui->setupUi(this);
}

TimerListWidget::~TimerListWidget()
{
    delete ui;
}

void TimerListWidget::changeEvent(QEvent *e)
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
