#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            time=dialog->getValues();
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->timerList);
    ui->timerList->addItem(listWidgetItem);
    TimerListItem* item=new TimerListItem;
    item->setTime(time);
    listWidgetItem->setSizeHint(item->sizeHint());
    ui->timerList->setItemWidget(listWidgetItem,item);
}


