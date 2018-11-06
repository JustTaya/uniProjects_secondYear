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
    void on_addTimerButton_clicked();
    void nonadd(){}

//    void on_timerList_itemPressed(QListWidgetItem *item);

    void on_addAlarmButton_clicked();
    void showTimerItems(int filter);
    void showAlarmItems(int filter);

private:
    Ui::MainWindow *ui;
    QWidget* timerList;
    QWidget* alarmList;
    QList<TimerListItem*> timers;
    QList<AlarmListItem*> alarms;
    void noFilter_t();
    void showEnabled_t();
    void showDisabled_t();
    void noFilter_a();
    void showEnabled_a();
    void showDisabled_a();
};

#endif // MAINWINDOW_H
