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
    this->timer=new QTimer;
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

