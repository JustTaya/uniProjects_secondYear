#ifndef ALARMLISTITEM_H
#define ALARMLISTITEM_H

#ifdef HAVE_QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

namespace Ui {
class AlarmListItem;
}

class AlarmListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmListItem(QWidget *parent = 0);
    ~AlarmListItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AlarmListItem *ui;
};

#endif // ALARMLISTITEM_H
