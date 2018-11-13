#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H


#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>
#include <QMap>

struct TimerData
{
    QString name;
    int index;
    QTime time;
    int type;   //0 None    1 Delay for     2 Play after time
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
    explicit AddTimerDialog(TimerData* data,  QWidget *parent = nullptr);
    AddTimerDialog(int numb, QTime timer, QTime delay, QWidget *parent = nullptr);
    ~AddTimerDialog();
    TimerData* getData();
    void addTimer(QString name, int index);
protected:
    void changeEvent(QEvent *e);
private slots:
    void on_timerName_textChanged();

    void on_Type_currentIndexChanged(int index);

private:
    Ui::AddTimerDialog *ui;
    TimerData* data;
    QMap<QString,int> timers;
    void setStartData(int numb);
};

#endif // ADDTIMERDIALOG_H
