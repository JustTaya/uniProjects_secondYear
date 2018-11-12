#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H


#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>

struct TimerData
{
    QString name;
    int index;
    QTime time;
    QTime delay;
    int sound;
    int triggerAfter;
};

namespace Ui {
class AddTimerDialog;
}

class AddTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTimerDialog(int numb, QWidget *parent = nullptr);
    explicit AddTimerDialog(int numb, QTime timer, QTime delay, QWidget *parent = nullptr);
    ~AddTimerDialog();
    TimerData* getData();
protected:
    void changeEvent(QEvent *e);


private slots:
    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_Delay_userTimeChanged(const QTime &time);

    void on_Alarms_currentIndexChanged(int index);

    void on_Timers_currentIndexChanged(int index);

    void on_timerName_textChanged();

private:
    Ui::AddTimerDialog *ui;
    TimerData* data;
    void setStartData(int numb);
};

#endif // ADDTIMERDIALOG_H
