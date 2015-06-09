#include "archive.h"

Archive::Archive(int m, int y, string h)
{
    string months[12]={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};
    month=m;
    year=y;
    HOME=h;
    monthName=months[month-1];
    xmlDom=new XmlDom(HOME);
    ca=xmlDom->getCaMois(month, year);
}

Archive::~Archive()
{
    delete xmlDom;
}


string Archive::getYear() const
{
    stringstream ss;
    ss << year;
    return ss.str();
}

string Archive::getMonthName() const
{
    return monthName;
}

string Archive::getCa() const
{
    stringstream ss;
    ss << ca;
    return ss.str();
}



