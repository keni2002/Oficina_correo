#include "Telegrama.h"

Telegrama::Telegrama(string destinatario, string dir_destino, string remitente,int dia, int mes,int anio,int cntWords,float impuesto):PostBag(destinatario,dir_destino,remitente, dia,mes,anio)
{
    this -> cntWords = cntWords;
    this -> impuesto = impuesto;
    //ctor
}
float Telegrama::calcPrice(){
    return cntWords * 0.10 * impuesto;
}
string Telegrama::toString(){
    string cad = "";
    cad = PostBag::toString();//polifor

    cad+= "Cantidad de palabras: " + to_string(cntWords) +"\n";
    cad+= "Impuesto Aplicado: $" + to_string(impuesto)+"\n";
    return cad;
}
string Telegrama::cad_file_out(){
    string cad = "";
    cad = PostBag::cad_file_out();
    cad += to_string(cntWords)+"*"+to_string(impuesto)+"*0*0*0";
    return cad;
}
int Telegrama::getCntWords(){
    return cntWords;
}
Telegrama::~Telegrama()
{
    //dtor
}


