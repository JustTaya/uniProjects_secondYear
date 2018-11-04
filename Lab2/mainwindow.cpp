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

void MainWindow::on_pushButton_clicked()
{
    QListWidgetItem* listWidgetItem=new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(listWidgetItem);
    TimerScrollItem* item=new TimerScrollItem;
    listWidgetItem->setSizeHint(item->sizeHint());
    ui->listWidget->setItemWidget(listWidgetItem,item);
}
