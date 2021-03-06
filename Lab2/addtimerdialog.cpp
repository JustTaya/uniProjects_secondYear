#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"

AddTimerDialog::AddTimerDialog(int numb,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);
    this->data=new TimerData;
    data->index=numb;

    this->setStartData(numb);
    ui->Delay->setVisible(false);
    ui->Delay->setDisabled(true);

    QRegExp rx("[A-Z,a-z,0-9, ]{1,19}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->timerName->setValidator(validator);
    ui->timerName->setText("Timer "+QString::number(data->index));

}


AddTimerDialog::AddTimerDialog(TimerData* data,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);
    this->data=new TimerData;

    this->data->index=data->index;
    ui->timeEdit->setTime(data->time);
    ui->Type->setCurrentIndex(data->type);
    ui->Alarms->setCurrentIndex(data->sound);
    ui->Timers->setCurrentIndex(data->triggerAfter);
    if(data->type>0)
    {
        ui->Delay->setVisible(true);
        ui->Delay->setEnabled(true);
        ui->Delay->setTime(data->delay);
    }
    else
    {
        ui->Delay->setVisible(false);
        ui->Delay->setDisabled(true);
    }

    QRegExp rx("[A-Z,a-z,0-9, ]{1,19}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->timerName->setValidator(validator);
    ui->timerName->setText(data->name);

}

AddTimerDialog::AddTimerDialog(int numb, QTime timer, QTime delay,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);
    this->data=new TimerData;

    data->index=numb;

    ui->timerName->setText("Timer "+QString::number(data->index));
    ui->timeEdit->setTime(timer);
    ui->Delay->setTime(delay);
    this->setStartData(numb);

    QRegExp rx("[A-Z,a-z,0-9, ]{1,19}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->timerName->setValidator(validator);
    ui->timerName->setText("Timer "+QString::number(data->index));

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
    data->time=ui->timeEdit->time();
    data->type=ui->Type->currentIndex();
    data->delay=ui->Delay->time();
    data->sound=ui->Alarms->currentIndex();
    if(ui->Timers->currentIndex()!=0)
        data->triggerAfter=this->timers[ui->Timers->currentText()];
    else
        data->triggerAfter=-1;
    return this->data;
}


void AddTimerDialog::setStartData(int numb)
{
    data->name="Timer "+QString::number(numb);
    data->time=QTime::fromString("00:00:00");
    data->type=0;
    data->delay=QTime::fromString("00:00:00");
    data->sound=0;
    data->triggerAfter=0;
}

void AddTimerDialog::addTimer(QString name,int index)
{
    ui->Timers->addItem(name);
    this->timers.insert(name,index);
}

void AddTimerDialog::on_timerName_textChanged(const QString &arg1)
{
    data->name=arg1;
}

void AddTimerDialog::on_Type_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui->Delay->setVisible(false);
        ui->Delay->setDisabled(true);
    }
    else
    {
        ui->Delay->setVisible(true);
        ui->Delay->setEnabled(true);
    }
}


