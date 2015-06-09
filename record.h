#ifndef RECORD_H
#define RECORD_H

#include <QDate>

class Record
{
public:
    Record(QDate* qDate, double ca);
    Record(QDate *qDate);
    QDate* getQDate();
    double getCa();
private:
    QDate *qDate;
    double ca;
};

#endif // RECORD_H
