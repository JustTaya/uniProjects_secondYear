#include "timerlistitem.h"
#include "ui_timerlistitem.h"

TimerListItem::TimerListItem(const QList<TimerListItem*>& list,TimerData* data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerListItem)
{
    ui->setupUi(this);
    this->state=on;
    this->setPauseMode();
    this->tmpTimer=new QTimer;
    this->timer=new QTimer;
    this->delayTimer=new QTimer;
    this->alarmTimer=new QTimer;

    this->data=data;
    this->setData(list,data);

    connect(this->timer,SIGNAL(timeout()),this,SLOT(alarm()));
    connect(this->delayTimer,SIGNAL(timeout()),this,SLOT(delayTimeOut()));
    connect(this->tmpTimer,SIGNAL(timeout()),this,SLOT(step()));
    connect(ui->playButton,SIGNAL(clicked()),this,SLOT(run()));
}

TimerListItem::~TimerListItem()
{
    delete ui;
}


void TimerListItem::setData( const QList<TimerListItem*>& list,TimerData* data)
{
    ui->Name_label->setText(data->name);

    ui->timerTime->setText(data->time.toString("hh:mm:ss"));
    this->initTime=QTime(0,0,0).secsTo(data->time);
    this->time=this->initTime;
    switch(data->type)
    {
    case 0:
    {
        ui->delayedLabel->setVisible(false);
        ui->delayedTime->setVisible(false);
        this->delay=0;
        this->initDelay=0;
        break;
    }
    case 1:
    {
        ui->delayedLabel->setVisible(true);
        ui->delayedTime->setVisible(true);
        ui->delayedTime->setText(data->delay.toString("hh:mm:ss"));
        ui->delayedLabel->setText("Delayed for:");
        this->initDelay=QTime(0,0,0).secsTo(data->delay);
        this->delay=this->initDelay;
        break;
    }
    case 2:
    {
        ui->delayedLabel->setVisible(true);
        ui->delayedTime->setVisible(true);
        this->delay=0;
        this->initDelay=0;
        ui->delayedLabel->setText("Run at:");
        ui->delayedTime->setText(data->delay.toString("hh:mm:ss"));

            delete alarmTimer;
            alarmTimer=nullptr;

        runAlarmTimer();
        connect(this->alarmTimer,SIGNAL(timeout()),this,SLOT(run()));
    }
    }

    if(data->triggerAfter!=-1)
    {
        foreach(auto iter,list)
        {
            if(iter->getIndex()==data->triggerAfter)
            {
                ui->delayedLabel->setText("Trigger after "+iter->getName());
                connect(iter->timer,SIGNAL(timeout()),this,SLOT(run()));
                break;
            }
        }
    }

    this->playlist=new QMediaPlaylist;

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

QString TimerListItem::getName()
{
    return ui->Name_label->text();
}

int TimerListItem::getIndex()
{
    return this->data->index;
}

State TimerListItem::getState()
{
    return this->state;
}

int TimerListItem::getType()
{
    return this->data->type;
}

void TimerListItem::run()
{
    setPlayMode();
    if(this->data->type==2 && alarmTimer!=nullptr)
    {
        alarmTimer->stop();
        delete this->alarmTimer;
        this->alarmTimer=nullptr;
    }
    if(this->delay>0)
    {
        this->tmpTimer->start(1000);
        this->delayTimer->start(this->delay*1000);
    }
    else
    {
        this->tmpTimer->start(1000);
        this->timer->start(this->time*1000);
    }
}

void TimerListItem::delayTimeOut()
{
    this->tmpTimer->stop();
    this->delayTimer->stop();
    ui->delayedTime->setVisible(false);
    ui->delayedLabel->setVisible(false);
    delay=-1;
    this->tmpTimer->start(1000);
    this->timer->start(this->time*1000);
}

void TimerListItem::step()
{
    if(delay>0)
    {
        this->delay--;
        QTime t=QTime(0,0,0).addSecs(this->delay);
        ui->delayedTime->setText(t.toString("hh:mm:ss"));
    }
    else
    {
       this->time--;
       QTime t=QTime(0,0,0).addSecs(this->time);
       ui->timerTime->setText(t.toString("hh:mm:ss"));
    }
}

void TimerListItem::on_deleteButton_clicked()
{
    this->state=del;
    this->close();
}

void TimerListItem::on_pauseButton_clicked()
{
    if(this->delay>0)
        this->delayTimer->stop();
    else
        this->timer->stop();
    this->tmpTimer->stop();
    setPauseMode();
}

void TimerListItem::on_stopButton_clicked()
{
    this->tmpTimer->stop();
    setPauseMode();
    if(initDelay!=0)
    {
        this->delayTimer->stop();
        QTime t=QTime(0,0,0).addSecs(this->initDelay);
        ui->delayedTime->setText(t.toString("hh:mm:ss"));
        this->delay=this->initDelay;
    }
    else
    {
        this->timer->stop();
        QTime t=QTime(0,0,0).addSecs(this->initTime);
        ui->timerTime->setText(t.toString("hh:mm:ss"));
        this->time=this->initTime;
    }
}


void TimerListItem::alarm()
{
    setPauseMode();
    this->tmpTimer->stop();
    this->timer->stop();
    this->delay=this->initDelay;
    this->time=this->initTime;
    if(initDelay>0)
    {
        ui->delayedLabel->setVisible(true);
        ui->delayedTime->setVisible(true);
        QTime t=QTime(0,0,0).addSecs(this->initDelay);
        ui->delayedTime->setText(t.toString("hh:mm:ss"));
    }

    QTime t=QTime(0,0,0).addSecs(this->initTime);
    ui->timerTime->setText(t.toString("hh:mm:ss"));

    TimerAlarm* alarmDialog=new TimerAlarm(this->playlist,data->name);
    alarmDialog->setTimer();
    alarmDialog->show();
    if(this->data->type==2)
    {
        runAlarmTimer();
    }
}

void TimerListItem::runAlarmTimer()
{
    this->alarmTimer=new QTimer;
    alarmTimer->start(abs(QTime(0,0,0).secsTo(data->delay)-
                          QTime(0,0,0).secsTo(QTime::currentTime()))*1000);
}

void TimerListItem::setPlayMode()
{
    ui->playButton->setDisabled(true);
    ui->playButton->setVisible(false);
    ui->pauseButton->setEnabled(true);
    ui->pauseButton->setVisible(true);
    ui->stopButton->setEnabled(true);
    ui->stopButton->setVisible(true);
    this->state=on;
}
void TimerListItem::setPauseMode()
{
    ui->playButton->setEnabled(true);
    ui->playButton->setVisible(true);
    ui->pauseButton->setDisabled(true);
    ui->pauseButton->setVisible(false);
    ui->stopButton->setDisabled(true);
    ui->stopButton->setVisible(false);
    this->state=off;
}

void TimerListItem::on_editButton_clicked()
{
    setPauseMode();
    timer->stop();
    tmpTimer->stop();

    AddTimerDialog* dialog=new AddTimerDialog(this->data);
    foreach(auto iter,timers)
    {
        if(iter->getState()!=del && iter!=this)
            dialog->addTimer(iter->getName(),iter->getIndex());
    }
    dialog->show();
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));
        this->data=dialog->getData();
        this->setData(this->timers,this->data);
    }
}

void TimerListItem::setTimerList(const QList<TimerListItem*>& list)
{
    this->timers=list;
}

