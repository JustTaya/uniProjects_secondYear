#ifndef TIMERSCROLLITEM_H
#define TIMERSCROLLITEM_H

#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

namespace Ui {
class TimerScrollItem;
}

class TimerScrollItem : public QWidget
{
    Q_OBJECT

public:
    explicit TimerScrollItem(QWidget *parent = 0);
    ~TimerScrollItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TimerScrollItem *ui;
};

#endif // TIMERSCROLLITEM_H
