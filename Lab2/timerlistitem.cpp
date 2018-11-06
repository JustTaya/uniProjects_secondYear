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

    connect(timer,SIGNAL(timeout()),this, SLOT(alarm()));
    connect(tmpTimer,SIGNAL(timeout()),this,SLOT(step()));
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

void TimerListItem::run()
{
    this->timer->start(this->initTime);
    this->tmpTimer->start(1000);
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
    ui->playButton->setEnabled(true);
    ui->playButton->setVisible(true);
    ui->pauseButton->setDisabled(true);
    ui->pauseButton->setVisible(false);
    ui->stopButton->setDisabled(true);
    ui->stopButton->setVisible(false);
    this->state=off;
}

void TimerListItem::on_stopButton_clicked()
{
    this->timer->stop();
    this->tmpTimer->stop();
    ui->playButton->setEnabled(true);
    ui->playButton->setVisible(true);
    ui->pauseButton->setDisabled(true);
    ui->pauseButton->setVisible(false);
    ui->stopButton->setDisabled(true);
    ui->stopButton->setVisible(false);
    this->state=off;
    QTime t=QTime(0,0,0).addSecs(this->initTime);
    ui->label->setText(t.toString("hh:mm:ss"));
    this->time=this->initTime;
}

void TimerListItem::on_playButton_clicked()
{
    ui->playButton->setDisabled(true);
    ui->playButton->setVisible(false);
    ui->pauseButton->setEnabled(true);
    ui->pauseButton->setVisible(true);
    ui->stopButton->setEnabled(true);
    ui->stopButton->setVisible(true);
    this->state=on;
    this->run();
}

void TimerListItem::step()
{
       this->time--;
       QTime t=QTime(0,0,0).addSecs(this->time);
       ui->label->setText(t.toString("hh:mm:ss"));
}

void TimerListItem::alarm()
{

}
