#include "logmaker.h"

LogMaker::LogMaker(QObject *parent) : QObject(parent)
{
    this->logs=new Logs;
}

void LogMaker::save(QList<TimerListItem*> timers, QList<AlarmListItem*> alarms, Settings* settings)
{
    QFile logs_t("TimersLog.txt");
    if(!logs_t.open(QIODevice::WriteOnly))
    {
        std::cerr<<"Check your log files. Can't save data."<<std::endl;
        return;
    }
    int tmp;
    QTextStream stream_t(&logs_t);
    for(auto iter:timers)
    {
        tmp=iter->getInitTime();
      stream_t<<tmp<<"\n";
    }
    logs_t.close();


    QFile logs_a("AlarmsLog.txt");
    if(!logs_a.open(QIODevice::WriteOnly))
    {
      std::cerr<<"Check your log files. Can't save data."<<std::endl;
      return;
    }
    QTextStream stream_a(&logs_a);
    for(auto iter:alarms)
        stream_a<<iter->getTimeFormat()<<" "<<iter->getInitTime()<<" "<<
               iter->checkDay(0)<<" "<< iter->checkDay(1)<<" "<< iter->checkDay(2)<<" "<< iter->checkDay(3)<<
                " "<<iter->checkDay(4)<<" "<<iter->checkDay(5)<<" "<< iter->checkDay(6)<<"\n";
    logs_a.close();


    QFile logs_s("Settings_Log.txt");
    if(!logs_s.open(QIODevice::WriteOnly))
    {
      std::cerr<<"Check your log files. Can't save data."<<std::endl;
      return;
    }

    QTextStream stream_s(&logs_s);

    stream_s<<settings->getTimeFormat()<<" "<<settings->getTimerPlaylist()<<" "
           <<settings->getAlarmPlaylist()<<"\n";
    logs_s.close();

}

Logs* LogMaker::getLogs()
{
    this->logs->settings=new Settings;
    int tmp=0;


    QFile logs_s("Settings_Log.txt");
    if(!logs_s.open(QIODevice::ReadOnly))
    {
      return nullptr;
    }

    QTextStream stream_s(&logs_s);
    int format,timer_playlist,alarm_playlist;

    stream_s>>format>>timer_playlist>>alarm_playlist;

    switch(format)
    {
    case 0:
        this->logs->settings->timeFormat="hh:mm:ss";
        break;
    case 1:
        this->logs->settings->timeFormat="h:mm AP";
        break;
    }

    this->logs->settings->timerPlaylist=new QMediaPlaylist;

    switch(timer_playlist)
    {
    case 0:
        this->logs->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
        break;
    case 1:
        this->logs->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm2.mp3")));
        break;
    case 2:
        this->logs->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm3.wav")));
        break;
    }

    this->logs->settings->alarmPlaylist=new QMediaPlaylist;

    switch(alarm_playlist)
    {
    case 0:
        this->logs->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
        break;
    case 1:
        this->logs->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm2.mp3")));
        break;
    case 2:
        this->logs->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm3.wav")));
        break;
    }

    logs_s.close();


    QFile logs_t("TimersLog.txt");
    if(!logs_t.open(QIODevice::ReadOnly))
    {
        return nullptr;
    }
    QTextStream stream_t(&logs_t);
    while(!stream_t.atEnd())
    {
      stream_t>>tmp;
      TimerListItem* item=new TimerListItem;
      item->setPlaylist(this->logs->settings->timerPlaylist);
      item->setDeley(QTime(0,0,0).addSecs(0));
      item->setTime(QTime(0,0,0).addSecs(tmp));
      this->logs->timers.push_back(item);
    }
    logs_t.close();


    QFile logs_a("AlarmsLog.txt");
    if(!logs_a.open(QIODevice::ReadOnly))
    {
      return nullptr;
    }
    QTextStream stream_a(&logs_a);
    while(!stream_a.atEnd()){
        int timeFormat,initTime;
        int* week=new int[7];
        bool* w=new bool[7];
        stream_a>>timeFormat>>initTime>>week[0]>>week[1]
               >>week[2]>>week[3]>>week[4]>>week[5]>>week[6];
        for(size_t i=0;i<7;i++)
        {
            if(week[0]==1)
                w[0]=true;
            else
                w[0]=false;
        }
        AlarmListItem* item=new AlarmListItem;
        item->setTimeFormat(this->logs->settings->timeFormat);
        item->setWeek(w);
        item->setPlaylist(this->logs->settings->alarmPlaylist);
        item->setTime(QTime(0,0,0).addSecs(initTime));
        this->logs->alarms.push_back(item);
    }

    logs_a.close();
    return this->logs;
}
