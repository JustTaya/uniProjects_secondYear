#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timerList=new QWidget;
    this->timerList->setLayout(new QVBoxLayout);
    ui->timerList->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->timerList->setWidget(this->timerList);

    this->alarmList=new QWidget;
    this->alarmList->setLayout(new QVBoxLayout);
    ui->alarmList->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->alarmList->setWidget(this->alarmList);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_addTimerButton_clicked()
{
    AddTimerDialog* dialog=new AddTimerDialog;
    dialog->show();
    QTime time;
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted(QTime)),this,SLOT(nonadd()));
        time=dialog->getValues();
        TimerListItem* item=new TimerListItem;
        item->setTime(time);
        this->timerList->layout()->addWidget(item);
        this->timers.push_back(item);
    }
}


void MainWindow::on_addAlarmButton_clicked()
{
    AddAlarmDialog* dialog=new AddAlarmDialog;
    dialog->show();
    if(dialog->exec())
    {
        QTime time;
        connect(dialog,SIGNAL(accepted(QTime)),this,SLOT(nonadd()));
        time=dialog->getValues();
        AlarmListItem* item=new AlarmListItem;
        item->setTime(time);
        this->alarmList->layout()->addWidget(item);
        this->alarms.push_back(item);
    }
}

void MainWindow::on_actionNo_filter_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
        iter->setVisible(true);
}

void MainWindow::on_actionShow_enabled_triggered()
{
    foreach(TimerListItem* iter,this->timers)
    {
        if(iter->getState()==on)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->getState()==on)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionShow_disabled_triggered()
{
    foreach(TimerListItem* iter,this->timers)
    {
        if(iter->getState()==off)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->getState()==off)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}
