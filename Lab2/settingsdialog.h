#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>
#include <QString>
#include <QMediaPlaylist>

struct Settings
{
    QString timeFormat;
    QMediaPlaylist* alarmPlaylist;
    QMediaPlaylist* timerPlaylist;

    int getTimeFormat()
    {
        if(timeFormat=="hh:mm:ss")
            return 0;
        return 1;
    }

    int getTimerPlaylist()
    {
        if(alarmPlaylist->media(0)==QMediaContent(QUrl("qrc:/Alarm1.mp3")))
            return 0;
        if(alarmPlaylist->media(0)==QMediaContent(QUrl("qrc:/Alarm2.mp3")))
            return 1;
        return 2;
    }
    int getAlarmPlaylist()
    {
        if(timerPlaylist->media(0)==QMediaContent(QUrl("qrc:/Alarm1.mp3")))
            return 0;
        if(timerPlaylist->media(0)==QMediaContent(QUrl("qrc:/Alarm2.mp3")))
            return 1;
        return 2;
    }
};

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    Settings* getSettings()
    {
        return this->settings;
    }

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_timerFormat1_clicked();

    void on_TimeFormat2_clicked();

    void on_timerSound_activated(int index);

    void on_AlarmSound_activated(int index);

private:
    Ui::SettingsDialog *ui;
    Settings* settings;
};

#endif // SETTINGSDIALOG_H
