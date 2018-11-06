#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include "addtimerdialog.h"
#include "timerlistitem.h"
#include <QTime>
#include <QListWidgetItem>
#include <memory>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_addTimerButton_clicked();
    void nonadd(){};

//    void on_timerList_itemPressed(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QWidget* timerList;
    QList<TimerListItem*> timers;
    //QList<AlarmListItem*> alarms;
    QTimer* timer;
};

#endif // MAINWINDOW_H
