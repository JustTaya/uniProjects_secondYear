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
    this->timer_numb=0;
    this->alarm_numb=0;

    this->alarmList=new QWidget;
    this->alarmList->setLayout(new QVBoxLayout);
    ui->alarmList->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->alarmList->setWidget(this->alarmList);    
}

MainWindow::~MainWindow()
{
    //this->logMaker->save(this->timers,this->alarms,this->settings);
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
    AddTimerDialog* dialog=new AddTimerDialog(this->timer_numb);
    foreach(auto iter,timers)
    {
        if(iter->getState()!=del)
            dialog->addTimer(iter->getName(),iter->getIndex());
    }
    dialog->show();
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));

        ++this->timer_numb;
        TimerListItem* item=new TimerListItem(this->timers,dialog->getData());
        this->timerList->layout()->addWidget(item);
        this->timers.push_back(item);
    }
    foreach(auto iter,timers)
        iter->setTimerList(this->timers);
}


void MainWindow::on_addAlarmButton_clicked()
{
    AddAlarmDialog* dialog=new AddAlarmDialog(this->alarm_numb);
    dialog->show();
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));
        AlarmListItem* item=new AlarmListItem(dialog->getData());
        this->alarmList->layout()->addWidget(item);
        this->alarms.push_back(item);
        alarm_numb++;
    }
}
/*
void MainWindow::on_actionNo_filter_triggered()
{

    foreach(AlarmListItem* iter,this->alarms)
        iter->setVisible(true);
}

void MainWindow::on_actionShow_enabled_triggered()
{

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

    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->getState()==off)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionSunday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(0))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionMonday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(1))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionTuesday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(2))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionWednesday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(3))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionThursday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(4))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionFriday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(5))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionSaturday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkDay(6))
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionEveryday_triggered()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
    foreach(AlarmListItem* iter,this->alarms)
    {
        if(iter->checkWeek())
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void MainWindow::on_actionChange_triggered()
{
    SettingsDialog* dialog=new SettingsDialog;
    if(dialog->exec())
    {
        connect(dialog,SIGNAL(accepted()),this,SLOT(nonadd()));
        this->settings=dialog->getSettings();
    }
}
*/

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
    {
        foreach(TimerListItem* iter,this->timers)
            iter->setVisible(true);
        break;
    }
    case 1:
    {
        foreach(TimerListItem* iter,this->timers)
            {
                if(iter->getState()==on)
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
            break;
        }
    case 2:
    {
        foreach(TimerListItem* iter,this->timers)
        {
            if(iter->getState()==off)
                iter->setVisible(true);
            else
                iter->setVisible(false);
        }
        break;
    }
    case 3:
    {
        foreach(TimerListItem* iter,this->timers)
        {
            if(iter->getType()!=0)
                iter->setVisible(true);
            else
                iter->setVisible(false);
        }
        break;
    }
    case 4:
    {
        foreach(TimerListItem* iter,this->timers)
        {
            if(iter->getType()==0)
                iter->setVisible(true);
            else
                iter->setVisible(false);
        }
        break;
    }
    }
}
