#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H


#ifdef HAVE_QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QDialog>
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
    void setValue(QTime);
    bool getFlag()
    {
        return this->flag;
    }

protected:
    void changeEvent(QEvent *e);


private:
    Ui::AddTimerDialog *ui;
    bool flag;
};

#endif // ADDTIMERDIALOG_H
