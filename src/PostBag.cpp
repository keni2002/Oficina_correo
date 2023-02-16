#include "PostBag.h"
//Correspondencia
PostBag::PostBag(string destinatario, string dir_destino, string remitente, int dia, int mes, int anio)
{
    this -> destinatario = destinatario;
    this -> dir_destino = dir_destino;
    this -> remitente = remitente;
    this ->dia =dia;
    this->mes=mes;
    this->anio=anio;
    fecha = new Fecha(dia,mes,anio);

    //ctor
}
PostBag::PostBag(){
    //CNT por defecto
}
string PostBag::toString(){
    string cad="";
    cad += "Destinatario: "+destinatario+"\n";
    cad += "Direccion: " + dir_destino +"\n";
    cad += "Remitente: "+remitente+"\n";
    cad += "Fecha: " + fecha->toString() + "\n";
    return cad;
}
string PostBag::cad_file_out(){
    return destinatario+"*"+dir_destino+"*"+remitente+"*"+to_string(dia)+"*"+to_string(mes)+"*"+to_string(anio)+"*";
}

PostBag::~PostBag()
{

    //dtor
}
string PostBag::getDestinatario(){
    return destinatario;
}
string PostBag::getDir_destino(){
    return dir_destino;
}
string PostBag::getRemitente(){
    return remitente;
}
bool PostBag::isToDay(){
    if(fecha->cntDias() == 0)
        return true;
    return false;
}


