#include "alarmlistitem.h"
#include "ui_alarmlistitem.h"

AlarmListItem::AlarmListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmListItem)
{
    ui->setupUi(this);

    this->state=off;
    this->timer=new QTimer;

    connect(timer,SIGNAL(timeout()),this, SLOT(alarm()));
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


void AlarmListItem::setTime(QTime time)
{
  ui->label->setText(time.toString(this->timeFormat));
  this->initTime=abs(QTime(0,0,0).secsTo(time));
  this->time=abs(this->initTime-QTime(0,0,0).secsTo(QTime::currentTime()));
}

void AlarmListItem::on_deleteButton_clicked()
{
    this->state=del;
    this->close();
}

void AlarmListItem::on_checkBox_stateChanged(int arg1)
{
    if(this->state==off)
        this->state=on;
    else
        this->state=off;
    if(arg1==Qt::Checked && this->checkDate())
            this->runTimer();
    else
        this->timer->start(24*60*60*1000);
}

void AlarmListItem::alarm()
{
    this->timer->stop();
    if(this->state==on){
    TimerAlarm* alarmDialog=new TimerAlarm(this->playlist);
        alarmDialog->setTimer();
        alarmDialog->show();
    }
    this->time=this->initTime;
}

void AlarmListItem::runTimer()
{
    this->timer->start(this->time*1000);
}


void AlarmListItem::on_editButton_clicked()
{
    AddAlarmDialog* dialog=new AddAlarmDialog;
    dialog->setFormat(this->timeFormat);
    dialog->show();
    if(dialog->exec())
    {
        QTime time;
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));
        time=dialog->getValues();
        this->setWeek(dialog->getWeek());
        this->setTime(time);
    }
}

bool AlarmListItem::checkDate()
{
    QDate date=QDate::currentDate();
    if(date.dayOfWeek() && this->week[0]==true)
        return true;
    if(this->week[date.dayOfWeek()-1]==true)
        return true;
    return false;
}

bool AlarmListItem::checkDay(int day)
{
    return this->week[day];
}

bool AlarmListItem::checkWeek()
{
    for(size_t i=0;i<7;i++)
        if(!this->week[i])
            return false;
    return true;
}
