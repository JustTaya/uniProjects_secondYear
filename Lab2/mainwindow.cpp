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

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
    {
        foreach(TimerListItem* iter,this->timers)
        {
            if(iter->getState()!=del)
                iter->setVisible(true);
        }
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
            if(iter->getState()!=del){
                if(iter->getType()!=0)
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 4:
    {
        foreach(TimerListItem* iter,this->timers)
        {
            if(iter->getState()!=del){
                if(iter->getType()==0)
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del)
                iter->setVisible(true);
        }
        break;
    }
    case 1:
    {
        foreach(AlarmListItem* iter,this->alarms)
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
        foreach(AlarmListItem* iter,this->alarms)
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
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkWeek())
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 4:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(0))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 5:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(1))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 6:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(2))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 7:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(3))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 8:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(4))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 9:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(5))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    case 10:
    {
        foreach(AlarmListItem* iter,this->alarms)
        {
            if(iter->getState()!=del){
                if(iter->checkDay(6))
                    iter->setVisible(true);
                else
                    iter->setVisible(false);
            }
        }
        break;
    }
    }
}
