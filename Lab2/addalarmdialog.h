#ifndef ADDALARMDIALOG_H
#define ADDALARMDIALOG_H

#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>

struct AlarmData
{
    QString name;
    int index;
    int timeFormat;
    QTime time;
    bool* days;
    int sound;
};

namespace Ui {
class AddAlarmDialog;
}

class AddAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlarmDialog(int index,QWidget *parent = nullptr);

    explicit AddAlarmDialog(AlarmData* data,QWidget *parent = nullptr);
    ~AddAlarmDialog();

    AlarmData* getData();
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_Sunday_stateChanged(int arg1);

    void on_Monday_stateChanged(int arg1);

    void on_Tuesday_stateChanged(int arg1);

    void on_Wednesday_stateChanged(int arg1);

    void on_Thursday_stateChanged(int arg1);

    void on_Friday_stateChanged(int arg1);

    void on_Saturday_stateChanged(int arg1);

    void on_timeFormat_currentIndexChanged(int index);

private:
    Ui::AddAlarmDialog *ui;
    bool* week;
    AlarmData* data;
    void setDay(int arg1,int day);
  };

#endif // ADDALARMDIALOG_H
