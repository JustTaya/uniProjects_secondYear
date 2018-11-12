#include "logmaker.h"

LogMaker::LogMaker(QObject *parent) : QObject(parent)
{
    this->logs=new Logs;
}
