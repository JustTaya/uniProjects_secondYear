#include "timerlistitem.h"
#include "ui_timerlistitem.h"

TimerListItem::TimerListItem(const QList<TimerListItem*>& list,TimerData* data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerListItem)
{
    ui->setupUi(this);
    this->setPauseMode();
    this->tmpTimer=new QTimer;
    this->timer=new QTimer;
    this->delayTimer=new QTimer;

    this->setData(list,data);

    connect(timer,SIGNAL(timeout()),this,SLOT(alarm()));
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
    ui->delayedTime->setText(data->delay.toString("hh:mm:ss"));
    this->initDelay=QTime(0,0,0).secsTo(data->delay);
    this->delay=this->initDelay;

    if(delay==0)
    {
        ui->delayedLabel->setVisible(false);
        ui->delayedTime->setVisible(false);
    }

    if(data->triggerAfter!=0)
    {
        int i=0;
        foreach(auto iter,list)
        {
            ++i;
            if(i==data->triggerAfter)
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
    return this->index;
}

State TimerListItem::getState()
{
    return this->state;
}

void TimerListItem::run()
{
    setPlayMode();
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

    //TimerAlarm* alarmDialog=new TimerAlarm(this->playlist);
    //alarmDialog->setTimer();
    //alarmDialog->show();
    setPauseMode();
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

    AddTimerDialog* dialog=new AddTimerDialog(0);
    dialog->show();
    QTime time;
    if(dialog->exec())
    {

    }
}

