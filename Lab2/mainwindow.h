#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include "addtimerdialog.h"
#include "addalarmdialog.h"
#include "timerlistitem.h"
#include "alarmlistitem.h"
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
    void nonadd(){}


    void on_addTimerButton_clicked();

    void on_addAlarmButton_clicked();
/*
    void on_actionNo_filter_triggered();

    void on_actionShow_enabled_triggered();

    void on_actionShow_disabled_triggered();

    void on_actionSunday_triggered();

    void on_actionMonday_triggered();

    void on_actionTuesday_triggered();

    void on_actionWednesday_triggered();

    void on_actionThursday_triggered();

    void on_actionFriday_triggered();

    void on_actionSaturday_triggered();

    void on_actionEveryday_triggered();

    void on_actionChange_triggered();
*/
    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QWidget* timerList;
    QWidget* alarmList;
    QList<TimerListItem*> timers;
    int timer_numb;
    int alarm_numb;
    QList<AlarmListItem*> alarms;
};

#endif // MAINWINDOW_H
