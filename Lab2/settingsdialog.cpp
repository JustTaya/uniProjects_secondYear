#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->settings=new Settings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SettingsDialog::on_timerFormat1_clicked()
{
    this->settings->timeFormat="hh:mm:ss";
}

void SettingsDialog::on_TimeFormat2_clicked()
{
    this->settings->timeFormat="h:mm AP";
}

void SettingsDialog::on_timerSound_activated(int index)
{
    this->settings->timerPlaylist=new QMediaPlaylist;
    switch(index)
    {
    case 0:
        this->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
        break;
    case 1:
        this->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm2.mp3")));
        break;
    case 2:
        this->settings->timerPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm3.wav")));
        break;
    }
}

void SettingsDialog::on_AlarmSound_activated(int index)
{
    this->settings->alarmPlaylist=new QMediaPlaylist;
    switch(index)
    {
    case 0:
        this->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm1.mp3")));
        break;
    case 1:
        this->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm2.mp3")));
        break;
    case 2:
        this->settings->alarmPlaylist->addMedia(QMediaContent(QUrl("qrc:/Alarm3.wav")));
        break;
    }
}
