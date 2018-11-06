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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddAlarmDialog *ui;
  };

#endif // ADDALARMDIALOG_H
