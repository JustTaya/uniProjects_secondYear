#ifndef TIMERLISTITEM_H
#define TIMERLISTITEM_H

#ifdef HAVE_QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "timeralarm.h"
#include "addtimerdialog.h"
#include <QTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtMath>


namespace Ui {
class TimerListItem;
}

class TimerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit TimerListItem(const QList<TimerListItem*>& list, TimerData* data,QWidget *parent = nullptr);
    ~TimerListItem();

    QString getName();

    int getIndex();

    State getState();

    int getType();

    void setTimerList(const QList<TimerListItem*>& list);

public slots:

    void run();

    void nonadd(){}

private slots:
    void on_deleteButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void delayTimeOut();

    void step();

    void alarm();

    void on_editButton_clicked();

private:
    Ui::TimerListItem *ui;
    State state;
    int index;
    TimerData* data;
    QList<TimerListItem*> timers;
    int initTime;   int time;
    int initDelay;  int delay;
    QTimer* tmpTimer;
    QTimer* timer;
    QTimer* delayTimer;
    QTimer* alarmTimer;
    QMediaPlaylist* playlist;
    void runTimer ();
    void setPlayMode();
    void setPauseMode();
    void setData(const QList<TimerListItem*>& list,TimerData* data);
    void runAlarmTimer();
   };

#endif // TIMERLISTITEM_H
