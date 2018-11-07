#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

AddAlarmDialog::AddAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);
    this->week=new bool[7];
    for(size_t i=0;i<7;i++)
        this->week[i]=false;
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

void AddAlarmDialog::on_Sunday_stateChanged(int arg1)
{
    setDay(arg1,0);
}

void AddAlarmDialog::on_Monday_stateChanged(int arg1)
{
     setDay(arg1,1);
}

void AddAlarmDialog::on_Tuesday_stateChanged(int arg1)
{
    setDay(arg1,2);
}

void AddAlarmDialog::on_Wednesday_stateChanged(int arg1)
{
    setDay(arg1,3);
}

void AddAlarmDialog::on_Thursday_stateChanged(int arg1)
{
    setDay(arg1,4);
}

void AddAlarmDialog::on_Friday_stateChanged(int arg1)
{
    setDay(arg1,5);
}

void AddAlarmDialog::on_Saturday_stateChanged(int arg1)
{
    setDay(arg1,6);
}

void AddAlarmDialog::setDay(int arg1,int day)
{
    if(arg1==Qt::Checked)
        this->week[day]=true;
    else
        this->week[day]=false;
}

 void AddAlarmDialog::setFormat(QString format)
 {
     ui->timeEdit->setDisplayFormat(format);
 }
