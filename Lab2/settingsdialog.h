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
