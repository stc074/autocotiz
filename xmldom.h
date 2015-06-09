#ifndef XMLDOM_H
#define XMLDOM_H

#include <QWidget>
#include <QtXml>
#include <QtGui>
#include <QMessageBox>
#include <QFile>
#include <iostream>
#include "record.h"

using namespace std;

class XmlDom : public QWidget
{
    Q_OBJECT
public:
    explicit XmlDom(string HOME);
    ~XmlDom();
    void addMonth(Record *rec);
    int exists(Record *rec);
    double getCaMois(int month, int year);

    string getHOME() const;
    void setHOME(const string &value);
    QStringList getAllYears();
    QStringList getMonthsOfYear(int);

private:
    QDomDocument* dom;
    QDomElement root;
    QFile* file;
    void saveDom();
    string HOME;
signals:

public slots:

};

#endif // XMLDOM_H
