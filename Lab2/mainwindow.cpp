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

    connect(ui->timerFilter,SIGNAL(activated(int)),this,SLOT(showTimerItems(int)));
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

void  MainWindow::showTimerItems(int filter)
{
    switch(filter){
    case 0:
        noFilter();
        break;
    case 1:
        showEnabled();
        break;
    case 2:
        showDisabled();
        break;
    }
}

/*TimerListItem* item=new TimerListItem;
        item->setTime(time);
        this->timerList->layout()->addWidget(item);
        this->timers.push_back(item);
*/

void MainWindow::noFilter()
{
    foreach(TimerListItem* iter,this->timers)
        iter->setVisible(true);
}


void  MainWindow::showEnabled()
{
    foreach(TimerListItem* iter,this->timers)
    {
        if(iter->getState()==on)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}

void  MainWindow::showDisabled()
{
    foreach(TimerListItem* iter,this->timers)
    {
        if(iter->getState()==off)
            iter->setVisible(true);
        else
            iter->setVisible(false);
    }
}
