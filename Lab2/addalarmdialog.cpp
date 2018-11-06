#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

AddAlarmDialog::AddAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);
}

AddAlarmDialog::~AddAlarmDialog()
{
    delete ui;
}

void AddAlarmDialog::changeEvent(QEvent *e)
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

QTime AddAlarmDialog::getValues()
{
    return ui->timeEdit->time();
}

void  AddAlarmDialog::setValue(QTime time)
{
    ui->timeEdit->setTime(time);
}
