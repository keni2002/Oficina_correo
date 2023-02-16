#ifndef POSTBAG_H
#define POSTBAG_H

#include "Fecha.h"
#include<iostream>
using namespace std;

class PostBag
{
    public:
        //constructores
        PostBag();
        PostBag(string,string,string,int,int,int);

        //polimorfismo
        virtual string toString();
        virtual string cad_file_out();
        virtual float calcPrice()=0;//abs

        //getters HERENCIA
        string getDestinatario();
        string getDir_destino();
        string getRemitente();
        bool isToDay();  //bueno para listar

        //setters


        //destructor
        virtual ~PostBag();

    protected:
        int dia, mes,anio;
        Fecha *fecha;//Lo añadi porque me fue menester
        string destinatario;//nombre a quien se le da el paquete
        string dir_destino; // direccion a llevar ese paquete
        string remitente; //nombre del que recibe

};

#endif // POSTBAG_H
