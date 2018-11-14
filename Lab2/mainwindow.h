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

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

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
