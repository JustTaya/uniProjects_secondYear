#ifndef ADDALARMDIALOG_H
#define ADDALARMDIALOG_H

#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
class AddAlarmDialog;
}

class AddAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlarmDialog(QWidget *parent = nullptr);
    ~AddAlarmDialog();
    QTime getValues();
    void setValue(QTime);
    bool* getWeek()
    {
        return this->week;
    }

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

private:
    Ui::AddAlarmDialog *ui;
    bool* week;
    void setDay(int arg1,int day);
  };

#endif // ADDALARMDIALOG_H
