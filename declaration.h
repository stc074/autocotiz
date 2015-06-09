#ifndef DECLARATION_H
#define DECLARATION_H

#include "xmldom.h"
#include <cmath>
#include <string>

using namespace std;

class Declaration
{
public:
    Declaration(int tri, int year, double pcPrinc, double pcForm, string HOME);
    double getCotis() const;
    void setCotis(double value);

    double getCotisForm() const;
    void setCotisForm(double value);

    int getNumTrimestre() const;
    void setNumTrimestre(int value);

    double getCotisTotal() const;
    void setCotisTotal(double value);

    double getCa1() const;
    void setCa1(double value);

    double getCa2() const;
    void setCa2(double value);

    double getCa3() const;
    void setCa3(double value);

    double getCatTotal() const;
    void setCatTotal(double value);

    string getMois1() const;
    void setMois1(const string &value);

    string getMois2() const;
    void setMois2(const string &value);

    string getMois3() const;
    void setMois3(const string &value);

private:
    double cotis;
    double cotisForm;
    int numTrimestre;
    double cotisTotal;
    double ca1;
    double ca2;
    double ca3;
    double catTotal;
    string mois1;
    string mois2;
    string mois3;
    //
    string HOME;
};

#endif // DECLARATION_H
