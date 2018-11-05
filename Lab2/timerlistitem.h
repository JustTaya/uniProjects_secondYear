#ifndef TIMERLISTITEM_H
#define TIMERLISTITEM_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace Ui {
class TimerListItem;
}

class TimerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit TimerListItem(QWidget *parent = 0);
    ~TimerListItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TimerListItem *ui;
};

#endif // TIMERLISTITEM_H
