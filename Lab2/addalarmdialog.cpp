#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

AddAlarmDialog::AddAlarmDialog(int index,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);
    for(size_t i=0;i<7;i++)
        this->week[i]=false;
    this->data=new AlarmData;
    this->data->index=index;
    ui->alarmName->setText("Alarm "+QString::number(data->index));
    ui->timeEdit->setDisplayFormat("h:mm AP");
}

AddAlarmDialog::AddAlarmDialog(AlarmData* data,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);
    this->data=data;

    for(size_t i=0;i<7;i++)
        this->week[i]=this->data->days[i];
    if(week[0])
       ui->Sunday->setCheckState(Qt::Checked);
   if(week[1])
       ui->Monday->setCheckState(Qt::Checked);
   if(week[2])
       ui->Tuesday->setCheckState(Qt::Checked);
   if(week[3])
       ui->Wednesday->setCheckState(Qt::Checked);
   if(week[4])
       ui->Thursday->setCheckState(Qt::Checked);
   if(week[5])
       ui->Friday->setCheckState(Qt::Checked);
   if(week[6])
       ui->Saturday->setCheckState(Qt::Checked);
    this->data->index=data->index;

   ui->timeFormat->setCurrentIndex(data->timeFormat);
   ui->Alarms->setCurrentIndex(data->sound);
   ui->timeEdit->setTime(data->time);
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

AlarmData* AddAlarmDialog::getData()
{
    this->data->name=ui->alarmName->toPlainText();
    this->data->timeFormat=ui->timeFormat->currentIndex();
    this->data->time=ui->timeEdit->time();
    for(size_t i=0;i<7;i++)
        this->data->days[i]=this->week[i];
    this->data->sound=ui->Alarms->currentIndex();
    return this->data;
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


void AddAlarmDialog::on_timeFormat_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->timeEdit->setDisplayFormat("h:mm AP");
        break;
    case 1:
        ui->timeEdit->setDisplayFormat("hh:mm:ss");
        break;
    }
}
