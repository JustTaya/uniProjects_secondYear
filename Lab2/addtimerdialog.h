#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H


#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QTime>

namespace Ui {
class AddTimerDialog;
}

class AddTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTimerDialog(QWidget *parent = nullptr);
    ~AddTimerDialog();
    QTime getValues();
    QTime getDelay();
    void setValue(QTime);

protected:
    void changeEvent(QEvent *e);


private:
    Ui::AddTimerDialog *ui;
};

#endif // ADDTIMERDIALOG_H
