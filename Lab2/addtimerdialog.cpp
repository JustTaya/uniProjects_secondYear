#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"

AddTimerDialog::AddTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);
}

AddTimerDialog::~AddTimerDialog()
{
    delete ui;
}

void AddTimerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QTime AddTimerDialog::getValues()
{
    return ui->timeEdit->time();
}

void  AddTimerDialog::setValue(QTime time)
{
    ui->timeEdit->setTime(time);
}

QTime AddTimerDialog::getDelay()
{
    return ui->Delay->time();
}


