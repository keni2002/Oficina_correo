#include "Carta.h"

Carta::Carta(string destinatario, string dir_destino, string remitente,int dia,int mes,int anio,bool esExterior):PostBag(destinatario,dir_destino,remitente, dia,mes,anio)
{
    //CONSTRUCTOR
    this -> esExterior = esExterior;

}
float Carta::calcPrice(){ //Posible Polimorfico
    int dias = fecha->cntDias();

    if(dias>10){
        if(esExterior)
            return 5 + 5; //es poca cantidad de dinero porque se tardaron. Le dimos 5 peso mas porque es de afuera sino no
        else
            return 5;

    }else if(dias<=10){//se le paga mas porque fue eficiente
        if(esExterior)
            return 8 + 3;
        else
            return 8;
    }

}

string Carta::toString(){
    string cad="";
    cad = PostBag::toString();

    string ext = esExterior ? "si":"no";
    cad += "Es del exterior? : " + ext + "\n";
    return cad;
}
string Carta::cad_file_out(){
    string cad = "";
    cad = PostBag::cad_file_out();
    cad+= "0*0*"+to_string(esExterior)+"*0*0";
    return cad;
}

Carta::~Carta()
{
    //dtor
}
