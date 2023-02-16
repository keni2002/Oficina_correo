#ifndef FECHA_H
#define FECHA_H
#include<iostream>
using namespace std;

class Fecha
{
    public:
        Fecha(); //default
        Fecha(int,int,int);
        string toString();
        virtual ~Fecha();

        //meths
        int cntDias();
        int getDayNow();
        int getMonthNow();
        int getYearNow();



    private:
        int dia,mes,anio;
        int testDia(int); //para que no se pase de 1->31 de bisiesto y febrrero hablamos despues
};

#endif // FECHA_H
