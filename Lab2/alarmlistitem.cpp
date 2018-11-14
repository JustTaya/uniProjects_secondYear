#include "alarmlistitem.h"
#include "ui_alarmlistitem.h"

AlarmListItem::AlarmListItem(AlarmData* data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmListItem)
{
    ui->setupUi(this);
    this->data=data;
    this->state=off;
    this->alarmTimer=new QTimer;

    connect(alarmTimer,SIGNAL(timeout()),this, SLOT(alarm()));
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

void AlarmListItem::setData()
{
    switch(data->timeFormat){
    case 0:
        ui->time_Label->setText(data->time.toString("h:mm AP"));
        break;
    case 1:
        ui->time_Label->setText(data->time.toString("hh:mm:ss"));
        break;
    }
    ui->time_Label->setText(data->time.toString(this->timeFormat));
    this->initTime=abs(QTime(0,0,0).secsTo(data->time));
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
 }

void AlarmListItem::alarm()
{
    this->alarmTimer->stop();
    if(this->state==on){
    TimerAlarm* alarmDialog=new TimerAlarm(this->playlist,this->data->name);
        alarmDialog->setTimer();
        alarmDialog->show();
    }
    this->time=this->initTime;
}

void AlarmListItem::runTimer()
{
    this->alarmTimer->start(this->time*1000);
}


void AlarmListItem::on_editButton_clicked()
{
    AddAlarmDialog* dialog=new AddAlarmDialog(this->data);
    dialog->show();
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted(QTime)),this,SLOT(nonadd()));
        this->data=dialog->getData();
        this->setData();
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
