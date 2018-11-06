#ifndef TIMERALARM_H
#define TIMERALARM_H

#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

enum State
{
    on,off,del  //del state to delete item from list on main form & from list of timer
};

namespace Ui {
class TimerAlarm;
}

class TimerAlarm : public QDialog
{
    Q_OBJECT

public:
    explicit TimerAlarm(QMediaPlaylist* playlist, QWidget *parent = nullptr);
    ~TimerAlarm();
    void setTimer();

protected:
    void changeEvent(QEvent *e);

private slots:
    void runAlarm();

    void on_quitButton_clicked();

private:
    Ui::TimerAlarm *ui;
    int counter;
    QTimer* timerAlarm;
    QMediaPlayer* player;
};

#endif // TIMERALARM_H
