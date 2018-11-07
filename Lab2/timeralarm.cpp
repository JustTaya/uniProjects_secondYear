#include "timeralarm.h"
#include "ui_timeralarm.h"

TimerAlarm::TimerAlarm(QMediaPlaylist* playlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerAlarm)
{
    ui->setupUi(this);

    this->counter=0;

    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    this->player=new QMediaPlayer;
    this->player->setPlaylist(playlist);
    this->player->play();

    this->timerAlarm=new QTimer;
    connect(this->timerAlarm,SIGNAL(timeout()),this,SLOT(runAlarm()));
}

TimerAlarm::~TimerAlarm()
{
    delete ui;
}

void TimerAlarm::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TimerAlarm::on_quitButton_clicked()
{
    this->timerAlarm->stop();
    this->player->stop();
    this->close();
}

void TimerAlarm::runAlarm()
{
  ++this->counter;
  QTime t=QTime(0,0,0).addSecs(this->counter);
  ui->label->setText("-"+t.toString("hh:mm:ss"));
}

void TimerAlarm::setTimer(){
    this->timerAlarm->start(1000);
}

