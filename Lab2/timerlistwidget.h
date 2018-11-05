#ifndef TIMERLISTWIDGET_H
#define TIMERLISTWIDGET_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace Ui {
class TimerListWidget;
}

class TimerListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerListWidget(QWidget *parent = 0);
    ~TimerListWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TimerListWidget *ui;
};

#endif // TIMERLISTWIDGET_H
