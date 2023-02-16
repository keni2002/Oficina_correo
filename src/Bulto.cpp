#include "Bulto.h"
#include<cmath>
Bulto::Bulto(string destinatario, string dir_destino, string remitente, int dia,int mes, int anio,float peso,int urgencia):PostBag(destinatario,dir_destino,remitente,dia,mes,anio)
{
    this->peso = peso;
    this->urgencia = urgencia;
    //ctor
}
float Bulto::calcPrice(){
    int dinero=1;//para que al muliplicar por el no se anule
    switch(urgencia){
        case 1:
            dinero=10;break;
        case 2:
            dinero=8;break;
    }
    return peso*4*dinero;
}
string Bulto::toString(){
    string cad="";
    cad = PostBag::toString();//polimorfismo
    cad += "Peso: " + to_string(peso)+"kg\n";
    cad += "Urgencia: ";
    switch(urgencia){
        case 1:
            cad+="Urgente\n";break;
        case 2:
            cad+="Medio urgente\n";break;
        case 3:
            cad+="Indiferente\n";break;
    }
    return cad;

}
string Bulto::cad_file_out(){
    return PostBag::cad_file_out()+"0*0*0*" + to_string(peso) +"*"+to_string(urgencia);
}
Bulto::~Bulto()
{
    //dtor
}
