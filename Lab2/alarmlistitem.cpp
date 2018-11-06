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

    this->alarmPlaylist=new QMediaPlaylist;
    this->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
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
  ui->label->setText(time.toString("h:mm AP"));
  this->initTime=abs(QTime(0,0,0).secsTo(time));
  this->time=this->initTime-QTime(0,0,0).secsTo(QTime::currentTime());
}

void AlarmListItem::on_deleteButton_clicked()
{
    this->state=del;
    this->close();
}

void AlarmListItem::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
        this->runTimer();
}

void AlarmListItem::alarm()
{
    this->timer->stop();
    TimerAlarm* alarmDialog=new TimerAlarm(this->alarmPlaylist);
    alarmDialog->setTimer();
    alarmDialog->show();
    this->time=this->initTime;
}

void AlarmListItem::runTimer()
{
    this->timer->start(this->time*1000);
}

