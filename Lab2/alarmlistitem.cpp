#include "alarmlistitem.h"
#include "ui_alarmlistitem.h"

AlarmListItem::AlarmListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmListItem)
{
    ui->setupUi(this);
}

AlarmListItem::~AlarmListItem()
{
    delete ui;
}

void AlarmListItem::changeEvent(QEvent *e)
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
