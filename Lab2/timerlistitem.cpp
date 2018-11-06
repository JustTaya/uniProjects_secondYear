#include "timerlistitem.h"
#include "ui_timerlistitem.h"

TimerListItem::TimerListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerListItem)
{
    ui->setupUi(this);
    ui->pauseButton->setDisabled(true);
    ui->pauseButton->setVisible(false);
    ui->stopButton->setDisabled(true);
    ui->stopButton->setVisible(false);
    this->state=off;
    this->tmpTimer=new QTimer;
    this->timer=new QTimer;

    connect(tmpTimer,SIGNAL(timeout()),this,SLOT(step()));
    connect(timer,SIGNAL(timeout()),this, SLOT(alarm()));

    this->alarmPlaylist=new QMediaPlaylist;
    this->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
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

void TimerListItem::setTime(QTime time)
{
  ui->label->setText(time.toString("hh:mm:ss"));
  this->initTime=QTime(0,0,0).secsTo(time);
  this->time=this->initTime;
}

void TimerListItem::runTimer()
{
    this->tmpTimer->start(1000);
    this->timer->start(this->initTime*1000);
}

void TimerListItem::on_deleteButton_clicked()
{
    this->state=del;
    this->close();
}

void TimerListItem::on_pauseButton_clicked()
{
    this->timer->stop();
    this->tmpTimer->stop();
    setPauseMode();
}

void TimerListItem::on_stopButton_clicked()
{
    this->timer->stop();
    this->tmpTimer->stop();
    setPauseMode();
    QTime t=QTime(0,0,0).addSecs(this->initTime);
    ui->label->setText(t.toString("hh:mm:ss"));
    this->time=this->initTime;
}

void TimerListItem::step()
{
       this->time--;
       QTime t=QTime(0,0,0).addSecs(this->time);
       ui->label->setText(t.toString("hh:mm:ss"));
}

void TimerListItem::alarm()
{
    this->timer->stop();
    this->tmpTimer->stop();
    TimerAlarm* alarmDialog=new TimerAlarm(this->alarmPlaylist);
    alarmDialog->setTimer();
    alarmDialog->show();
    setPauseMode();
    QTime t=QTime(0,0,0).addSecs(this->initTime);
    ui->label->setText(t.toString("hh:mm:ss"));
    this->time=this->initTime;
}

void TimerListItem::on_playButton_clicked()
{
    setPlayMode();
    runTimer();
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
