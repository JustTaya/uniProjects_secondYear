#ifndef ALARMLISTITEM_H
#define ALARMLISTITEM_H

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


namespace Ui {
class AlarmListItem;
}

class AlarmListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmListItem(QWidget *parent = nullptr);
    ~AlarmListItem();
    void setTime(QTime time);
    int getInitTime()
    {
        return this->initTime;
    }

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_deleteButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void alarm();

private:
    Ui::AlarmListItem *ui;
    State state;
    int initTime;
    int time;
    QTimer* timer;
    QTimer* alarmTimer;
    QMediaPlaylist* alarmPlaylist;
    void runTimer ();
};

#endif // ALARMLISTITEM_H
