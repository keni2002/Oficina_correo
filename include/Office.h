#ifndef OFFICE_H
#define OFFICE_H
//necesiades3
#include "PostBag.h"
#include "Fecha.h"
class Office {
public:
    //constructor
    Office(int);

    //Destructor
    virtual ~Office();


    //Adders
    void addPostBag(PostBag*);
    void addDespacho(PostBag*); //sobrecarga
    void addEntrega(PostBag*);


    //CARACTERISTICAS
    float calcEarns();
    string remitentesPrice();

    int despachar(int);
    bool entregar(string,string);
    int telegramasMayores(int);
    int cntCartaSentBy(string);
    string postBagMasRecibida();
    string mostrarSortTelegramas();


    //Salida de texto || working with files
    string out_postbags();
    string out_despacho();
    string out_entrega();


    //Estadistica
    string estadistica();
    string listarDespacho();






    //getter
    int getCntReal();
    int getCant_init();
    int getcntDespacho();
    int getcntEntregado();



private:
    //arreglos dinamicos
    PostBag **despacho; int cntTele,cntCarta,cntBulto;
    PostBag **postbags; int cntReal;
    PostBag **entregas; int cntEntr;

    int cant_init; // mi sustituto de sizeof

    void addDespacho(int,int);//al sumar un despacho ordenarlo correctamente

    //deleters
    void delDesp(int);
    void delPost(int);

};

#endif // OFFICE_H
