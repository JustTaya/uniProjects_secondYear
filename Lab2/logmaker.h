#ifndef LOGMAKER_H
#define LOGMAKER_H

#include "timerlistitem.h"
#include "alarmlistitem.h"
#include "settingsdialog.h"

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>

#include <iostream>
#include <memory>

struct Logs
{
    QList<TimerListItem*> timers;
    QList<AlarmListItem*> alarms;
    Settings* settings;
};

class LogMaker : public QObject
{
    Q_OBJECT
public:
    explicit LogMaker(QObject *parent = nullptr);
    void save(QList<TimerListItem*> timers, QList<AlarmListItem*> alarms, Settings* settings);
    void read();
    Logs* getLogs();

signals:

public slots:

private:
    Logs* logs;
};

#endif // LOGMAKER_H
