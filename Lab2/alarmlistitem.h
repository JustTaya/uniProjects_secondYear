#ifndef ALARMLISTITEM_H
#define ALARMLISTITEM_H

#ifdef HAVE_QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "timeralarm.h"
#include "addalarmdialog.h"
#include <QTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDate>


namespace Ui {
class AlarmListItem;
}

class AlarmListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmListItem(AlarmData* data,QWidget *parent = nullptr);
    ~AlarmListItem();
    void setTime(QTime time);
    int getInitTime()
    {
        return this->initTime;
    }

    State getState()
    {
        return this->state;
    }

    void setWeek(bool* week)
    {
        for(size_t i=0;i<7;i++)
            this->week[i]=week[i];
    }

    bool checkDay(int day);
    bool checkWeek();

    void setPlaylist(QMediaPlaylist* playlist)
    {
        this->playlist=playlist;
    }

    void setTimeFormat(QString timeFormat)
    {
        this->timeFormat=timeFormat;

    }

    int getTimeFormat()
    {
        if(this->timeFormat=="hh:mm:ss")
            return 0;
         return 1;
    }
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_deleteButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void alarm();

    void on_editButton_clicked();

    void newDay();

    void nonadd(){}

private:
    Ui::AlarmListItem *ui;
    State state;
    int initTime;
    int time;
    QTimer* delayTimer;
    QTimer* alarmTimer;
    QMediaPlaylist* playlist;
    bool week[7];
    QString timeFormat;
    AlarmData* data;
    void runTimer ();
    void checkDate();
    void setData();
};

#endif // ALARMLISTITEM_H
