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

    void setPlaylist(QMediaPlaylist* playlist)
    {
        this->playlist=playlist;
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

    void on_editButton_clicked();

private:
    Ui::TimerListItem *ui;
    State state;
    int initTime;
    int time;
    QTimer* tmpTimer;
    QTimer* timer;
    QTimer* alarmTimer;
    QMediaPlaylist* playlist;
    void runTimer ();
    void setPlayMode();
    void setPauseMode();
   };

#endif // TIMERLISTITEM_H
