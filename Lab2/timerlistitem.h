#ifndef TIMERLISTITEM_H
#define TIMERLISTITEM_H

#ifdef HAVE_QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "timeralarm.h"
#include <QTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>


enum State
{
    on,off,del  //del state to delete item from list on main form & from list of timer
};

namespace Ui {
class TimerListItem;
}

class TimerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit TimerListItem(QWidget *parent = nullptr);
    ~TimerListItem();
    void setTime(QTime time);
    int getInitTime()
    {
        return this->initTime;
    }

    State getState()
    {
        return this->state;
    }

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_deleteButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void step();

    void alarm();

    void on_playButton_clicked();

private:
    Ui::TimerListItem *ui;
    State state;
    int initTime;
    int time;
    QTimer* tmpTimer;
    QTimer* timer;
    QTimer* alarmTimer;
    QMediaPlaylist* alarmPlaylist;
    void runTimer ();
    void setPlayMode();
    void setPauseMode();
   };

#endif // TIMERLISTITEM_H
