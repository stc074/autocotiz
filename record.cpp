#include "record.h"

Record::Record(QDate* qDate, double ca)
{
    this->qDate=qDate;
    this->ca=ca;
}

Record::Record(QDate *qDate)
{
    this->qDate=qDate;
}

QDate* Record::getQDate() {
    return qDate;
}

double Record::getCa() {
    return ca;
}
