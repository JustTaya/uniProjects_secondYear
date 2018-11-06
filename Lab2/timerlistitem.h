#ifndef TIMERLISTITEM_H
#define TIMERLISTITEM_H


#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include <QTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QSound>
#include <QMediaPlayer>


enum State
{
    on,off,del  //del state to delete item from list on main form & from list of timer
};

namespace Ui {
class TimerListItem;
}

class TimerListItem : public QWidget,public QListWidgetItem
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

    void on_playButton_clicked();

    void step();

    void alarm();

private:
    Ui::TimerListItem *ui;
    State state;
    int initTime;
    int time;
    QTimer* tmpTimer;
    QTimer* timer;
    QTimer* alarmTimer;
    QMediaPlayer* alarmPlayer;
    void run ();

};

#endif // TIMERLISTITEM_H
