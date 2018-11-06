#ifndef TIMERLISTITEM_H
#define TIMERLISTITEM_H


#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include <QTime>
#include <QTimer>

enum State
{
    on,off,del  //del state to delete item from list on main form & from list of timer
};

namespace Ui {
class TimerListItem;
}

class TimerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit TimerListItem(QWidget *parent = nullptr);
    ~TimerListItem();
    void setTime(QTime time);
    int getInitTime()
    {
        return this->initTime;
    }

    State getState()
    {
        return this->state;
    }

public slots:
    void run ();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_deleteButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::TimerListItem *ui;
    State state;
    int initTime;
};

#endif // TIMERLISTITEM_H
