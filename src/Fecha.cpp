#include "Fecha.h"
#include<ctime>
int Fecha::testDia(int day){
    //MUY extranio pero el profesor quiere 30 dias y nos hace el trabajo mas facil
    if ( day > 0 && day <= 31 )
        return day;

    return 1;
}

int Fecha::getDayNow(){
    time_t now = time(0);
    tm* time = localtime(&now);
    return time->tm_mday;
}
int Fecha::getMonthNow(){
    time_t now = time(0);
    tm* time = localtime(&now);
    return 1+time->tm_mon;
}
int Fecha::getYearNow(){
    time_t now = time(0);
    tm* time = localtime(&now);
    return 1900+time->tm_year;
}

//Constructores
Fecha::Fecha(int pDia,int pMes,int anio) //pree dia
{
    //Constructor
    if(pMes > 0 && pMes <= 12)
        mes = pMes;
    else
        mes = 1;

    this->anio = anio;
    this->dia = testDia(pDia);


}
Fecha::Fecha(){

 //ctor by default
}

//diferencia de fechas
int Fecha::cntDias(){

    int anioA = getYearNow(); //A significa actual
    int mesA =  getMonthNow();
    int diaA =  getDayNow();

    return (diaA - dia) + (mesA-mes)*31 + (anioA-anio)*365;

}

string Fecha::toString(){
    string cad;
    cad = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    return cad;
}
Fecha::~Fecha()
{
    //dtor
}
