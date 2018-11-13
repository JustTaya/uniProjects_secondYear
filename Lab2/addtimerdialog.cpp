#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"

AddTimerDialog::AddTimerDialog(int numb,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);

    ui->timerName->setText("Timer "+QString::number(numb));
    this->setStartData(numb);
}

AddTimerDialog::AddTimerDialog(int numb, QTime timer, QTime delay,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);

    ui->timerName->setText("Timer "+QString::number(numb));
    ui->timeEdit->setTime(timer);
    ui->Delay->setTime(delay);
    this->setStartData(numb);
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

TimerData* AddTimerDialog::getData()
{
    data->name=ui->timerName->toPlainText();
    return this->data;
}

void AddTimerDialog::setStartData(int numb)
{
    this->data=new TimerData;
    data->name="Timer "+QString::number(numb);
    data->index=numb;
    data->time=QTime::fromString("00:00:00");
    data->delay=QTime::fromString("00:00:00");
    data->sound=0;
    data->triggerAfter=0;
}



void AddTimerDialog::on_timeEdit_userTimeChanged(const QTime &time)
{
    data->time=time;
}

void AddTimerDialog::on_Delay_userTimeChanged(const QTime &time)
{
    data->delay=time;
}

void AddTimerDialog::on_Alarms_currentIndexChanged(int index)
{
    data->sound=index;
}

void AddTimerDialog::on_Timers_currentIndexChanged(int index)
{
    data->triggerAfter=index;
}

void AddTimerDialog::addTimer(QString name)
{
    ui->Timers->addItem(name);
}

