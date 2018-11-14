#include "alarmlistitem.h"
#include "ui_alarmlistitem.h"

AlarmListItem::AlarmListItem(AlarmData* data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmListItem)
{
    ui->setupUi(this);
    this->data=data;
    this->state=off;
    this->playlist=new QMediaPlaylist;

    this->setData();
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
    ui->Name_label->setText(this->data->name);

    for(size_t i=0;i<7;i++)
        this->week[i]=this->data->days[i];
    switch(data->timeFormat){
   case 0:
        ui->time_Label->setText(data->time.toString("h:mm AP"));
        break;
    case 1:
        ui->time_Label->setText(data->time.toString("hh:mm:ss"));
        break;
    }

    this->initTime=abs(QTime(0,0,0).secsTo(data->time));
    this->alarmTimer=new QTimer;
    this->delayTimer=new QTimer;
    connect(alarmTimer,SIGNAL(timeout()),this, SLOT(alarm()));
    connect(delayTimer,SIGNAL(timeout()),this, SLOT(newDay()));

    switch(data->sound)
    {
    case 0:
        this->playlist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
        break;
    case 1:
        this->playlist->addMedia(QMediaContent(QUrl("qrc:/Alarm2.mp3")));
        break;
    case 2:
        this->playlist->addMedia(QMediaContent(QUrl("qrc:/Alarm3.wav")));
        break;
    }
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
    if(arg1==Qt::Checked)
            this->checkDate();
 }

void AlarmListItem::alarm()
{
    this->alarmTimer->stop();
    if(this->state==on){
    TimerAlarm* alarmDialog=new TimerAlarm(this->playlist,this->data->name);
        alarmDialog->setTimer();
        alarmDialog->show();
    }
    delete this->alarmTimer;
    delete this->delayTimer;
    this->setData();
    this->time=this->initTime;
}

void AlarmListItem::runTimer()
{
    this->time=abs(this->initTime-QTime(0,0,0).secsTo(QTime::currentTime()));
    this->alarmTimer->start(1000*this->time);
}


void AlarmListItem::on_editButton_clicked()
{
    AddAlarmDialog* dialog=new AddAlarmDialog(this->data);
    dialog->show();
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));
        delete alarmTimer;
        delete delayTimer;
        this->data=dialog->getData();
        this->setData();
    }  
}

void AlarmListItem::checkDate()
{
    int day=QDate::currentDate().dayOfWeek();

    if(this->week[day])
            runTimer();

    delayTimer->start(24*60*60*1000);
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

void AlarmListItem::newDay()
{
    alarmTimer->stop();
    checkDate();
}
