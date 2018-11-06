#ifndef ALARMLISTITEM_H
#define ALARMLISTITEM_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace Ui {
class AlarmListItem;
}

class AlarmListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmListItem(QWidget *parent = nullptr);
    ~AlarmListItem();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AlarmListItem *ui;
};

#endif // ALARMLISTITEM_H
