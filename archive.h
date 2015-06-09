#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <sstream>
#include <iostream>
#include "xmldom.h"

using namespace std;

class Archive
{
public:
    Archive(int , int, string);
    ~Archive();
    //
    int getMonth() const;

    string getYear() const;

    string getMonthName() const;

    string getCa() const;

private:
    int month;
    int year;
    string monthName;
    double ca;
    string HOME;
    XmlDom *xmlDom;
};

#endif // ARCHIVE_H
