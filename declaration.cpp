#include "declaration.h"

Declaration::Declaration(int tri, int year, double pcPrinc, double pcForm, string Home)
{
    HOME=Home;
    numTrimestre=tri;
    string mois[12]={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Décembre"};
    XmlDom *xmlDom=new XmlDom(HOME);
    int fstMois=numTrimestre*3;
    //cout << fstMois << endl;
    mois1=mois[fstMois];
    ca1=xmlDom->getCaMois(fstMois+1, year);
    mois2=mois[fstMois+1];
    ca2=xmlDom->getCaMois(fstMois+2, year);
    mois3=mois[fstMois+2];
    ca3=xmlDom->getCaMois(fstMois+3, year);
    catTotal=ca1+ca2+ca3;
    //
    cotis=floor(floor(catTotal)*pcPrinc/(double)100);
    cotisForm=floor(floor(catTotal)*pcForm/(double)100);
    cotisTotal=cotis+cotisForm;
    delete xmlDom;
}
double Declaration::getCotis() const
{
    return cotis;
}

void Declaration::setCotis(double value)
{
    cotis = value;
}
double Declaration::getCotisForm() const
{
    return cotisForm;
}

void Declaration::setCotisForm(double value)
{
    cotisForm = value;
}
int Declaration::getNumTrimestre() const
{
    return numTrimestre;
}

void Declaration::setNumTrimestre(int value)
{
    numTrimestre = value;
}
double Declaration::getCotisTotal() const
{
    return cotisTotal;
}

void Declaration::setCotisTotal(double value)
{
    cotisTotal = value;
}
double Declaration::getCa1() const
{
    return ca1;
}

void Declaration::setCa1(double value)
{
    ca1 = value;
}
double Declaration::getCa2() const
{
    return ca2;
}

void Declaration::setCa2(double value)
{
    ca2 = value;
}
double Declaration::getCa3() const
{
    return ca3;
}

void Declaration::setCa3(double value)
{
    ca3 = value;
}
double Declaration::getCatTotal() const
{
    return catTotal;
}

void Declaration::setCatTotal(double value)
{
    catTotal = value;
}
string Declaration::getMois1() const
{
    return mois1;
}

void Declaration::setMois1(const string &value)
{
    mois1 = value;
}
string Declaration::getMois2() const
{
    return mois2;
}

void Declaration::setMois2(const string &value)
{
    mois2 = value;
}
string Declaration::getMois3() const
{
    return mois3;
}

void Declaration::setMois3(const string &value)
{
    mois3 = value;
}











