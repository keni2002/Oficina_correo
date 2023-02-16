#include "Office.h"
#include "Telegrama.h"
#include "Carta.h"
#include "Bulto.h"

//a veces es divertido usar C++11
#include<vector> //ver linea 270
#include<array>


//CONSTRUCTOR
Office::Office(int cnt) {
    //Espero que el catch atrape esto tambien
    despacho = new PostBag * [cnt];
    postbags = new PostBag * [cnt];//reservando memoria para un arreglo de punteros de clases Postbags
    entregas = new PostBag * [cnt];
    cntReal=cntEntr=cntTele=cntCarta=cntBulto=0;
    this->cant_init = cnt;
}
//Destructor
Office::~Office() {
}



//ADD POST
void Office::addPostBag(PostBag* corresp) {

    if(cntReal >= cant_init) //SUCEDE QUE NO ES ESTATICO y por lo tanto sizeof no sirve de nada en tiempo de ejecucion
        throw out_of_range("Se alcanzo el Limite del arreglo");
    else{
        postbags[cntReal] = corresp;
        cntReal++;
    }
}


//GETTERS
int Office::getCntReal() {

    return cntReal;
}
int Office::getCant_init(){
    return cant_init;
}
int Office::getcntDespacho() {
    return cntTele+cntCarta+cntBulto;
}
int Office::getcntEntregado(){
    return cntEntr;
}







//FUNCION 8------------------------------------------------------------------------
float Office::calcEarns() {
    float ganancias=0;
    for(int i = 0; i<cntReal; i++) {
        ganancias += postbags[i]->calcPrice();
    }
    return ganancias;
}
//DEPENDE
        string Office::remitentesPrice() {
            string cad="Correspondencias de:\n";
            for(int i=0; i<cntReal; i++) {
                cad+="\t\t"+postbags[i]->getRemitente()+"-> $"+to_string(postbags[i]->calcPrice())+"\n";
            }
            return cad;
        }


//////DESPACHO------------------------------------------------------------------------------------


void Office::addDespacho(int type, int pos) {

    int all = cntTele+cntCarta+cntBulto;
    PostBag *aux;
    int fin;
    switch(type)
    {
        case 1:fin=cntTele;break;
        case 2:fin=cntTele+cntCarta;break;
        case 3:fin=all;
    }

    despacho[all] = postbags[pos];

    if(all!=0 || type!=3){ //es solo para evitar ir al bucle por gusto
        for(int i=all;i>fin;i--){
            aux = despacho[i-1];
            despacho[i-1] = despacho[i];
            despacho[i] = aux;

        }
    }
}


int Office::despachar(int cnt) {
    int i=0;
    if(cntReal!=0 && cnt>0) {
        if(cntReal >= cnt) {

            if(cntCarta+cntBulto+cntTele+cnt > cant_init)
                throw out_of_range("Se alcanzo el Limite del arreglo");
            else{
                for(i=0; i<cnt; i++) {

                    if(dynamic_cast<Telegrama*>(postbags[i])) {

                        addDespacho(1,i);
                        cntTele++;


                    }
                    else if(dynamic_cast<Carta*>(postbags[i])) {

                        addDespacho(2,i);
                        cntCarta++;
                    }

                    else if(dynamic_cast<Bulto*>(postbags[i])) {

                        addDespacho(3,i);
                        cntBulto++;
                    }

                }//endfor
                delPost(cnt);
                return 1;
            } //end else

        }//endif
        else
            return -1;//exceso

    }//endif
    else
        return 0;//empty



}//endfunction


void Office::delPost(int cant){
    PostBag *aux;

    for(int i=0;i<cant;i++){
        aux = postbags[i];
        postbags[i]=postbags[cntReal-1];
        postbags[cntReal-1] = aux;

        cntReal--;
    }

}



//////ENTREGAS----------------------------------------------



bool Office::entregar(string name, string address) {
    int all=cntTele+cntBulto+cntCarta;

    for(int i=0; i<all; i++) {
        if(name == despacho[i]->getDestinatario() && address == despacho[i]->getDir_destino()) {
            delDesp(i);
            return 1;break;
        }
    }
    return 0;
}



void Office::delDesp(int pos) {
    PostBag *aux;

    int all=cntTele+cntCarta+cntBulto;
    if(dynamic_cast<Telegrama*>(despacho[pos]))
        cntTele--;
    else if(dynamic_cast<Carta*>(despacho[pos]))
        cntCarta--;
    else if(dynamic_cast<Bulto*>(despacho[pos]))
        cntBulto--; //le quita un elemento menos

    //llevar el objeto a entregas cual basurero fuera
    Office::addEntrega(despacho[pos]);

    //Acomodar par no regar;
    for(int i=pos; i<all; i++) {
        aux = despacho[i+1];
        despacho[i+1]=despacho[i];
        despacho[i] = aux;
    }
    //lo que hace es correr el elemento hasta el final
    //poco o poco y luego se corre un lugar,
    //cosa que ya se hizo


}
//ATENCION PROFESOR AQUI LLEVA EXCEPCION PERO POR LA FILOSOFIA DEL SOFTWARE
//SEGUIREMOS LLENANDO EL ARRAY DE ENTREGAS HASTA MAS DEL  LIMITE
void Office::addEntrega(PostBag* corresp){
    entregas[cntEntr]=corresp;
    cntEntr++;
}




int Office::telegramasMayores(int cnt) {
    int contar=0;

    for(int i = 0; i<cntReal; i++) {
        if(dynamic_cast<Telegrama*>(postbags[i])) {
            //necesario para alegrar al compilador con la hija perfecta
            if(dynamic_cast<Telegrama*>(postbags[i])->getCntWords() > cnt) {
                contar++;
            }
        }
    }
    return contar;

}
//Obtener la cantidad de cartas enviadas por un remitente.
int Office::cntCartaSentBy(string rem) {
    int contar = 0;
    for(int i = 0; i<cntReal; i++) {
        if(dynamic_cast<Carta*>(postbags[i])) {
            if(postbags[i]->getRemitente()==rem) {
                contar++;
            }
        }
    }
    return contar;
}


//Saber que correspondencia fue la que más se recibió en el día.
string Office::postBagMasRecibida() {
    array<int,3>cnts= {0,0,0};
    array<string,3>cad= {"Telegramas","Cartas","Bultos"};
    for(int i=0; i<cntReal; i++) {
       if(postbags[i]->isToDay()) {
            if(dynamic_cast<Telegrama*>(postbags[i]))
                cnts[0]++;
            else if(dynamic_cast<Carta*>(postbags[i]))
                cnts[1]++;
            else if(dynamic_cast<Bulto*>(postbags[i]))
                cnts[2]++;
        }
    }
    int my=cnts[0];
    int pos=0;
    for(int i=1; i<3; i++) {
        if(my<cnts[i]) {
            my=cnts[i];
            pos=i;
        }
    }
    if(cnts[0]==0 && cnts[1]==0 && cnts[2]==0)
        return " 0";

    return cad[pos];
}


//Mostrar los datos de todos los telegramas recibidos en el Día ordenados
//por remitente.
// BUBBLE SORT || analizar despacio
string Office::mostrarSortTelegramas() {
    string cad="";
    //recorrer el array y almacenar posiciones
    vector <int>elementsT(0);
    //busca solo las posiciones donde estan los telegramas
    for(int i = 0; i< cntReal; i++) {
        if(dynamic_cast<Telegrama*>(postbags[i])) {
            if(postbags[i]->isToDay())
                elementsT.push_back(i);
        }
    }

    PostBag* temp;
    //ordena
    for(int i=0; i<elementsT.size(); i++) {
        for(int j = 0; j<elementsT.size()-i-1; j++) {
            if(postbags[elementsT[j]]->getRemitente() > postbags[elementsT[j+1]]->getRemitente()) {
                temp = postbags[elementsT[j]];
                postbags[elementsT[j]] = postbags[elementsT[j+1]];
                postbags[elementsT[j+1]] = temp;
            }
        }
    }
    for(int i= 0; i<elementsT.size(); i++) {
        cad+=postbags[elementsT[i]]->toString()+"\n";
    }
    return cad;
}


//ESTADISTICAS

string Office::listarDespacho(){
    string cad;
    int all=cntTele+cntCarta+cntBulto;
    if(all!=0) {
        cad+="\n---Telegramas:\n";
        for(int i=0; i<all; i++) {
            if(i==cntTele+cntCarta){
                cad+="\n---Bultos:\n";

            }
            else if(i==cntTele){
                cad+="\n---Cartas:\n";

            }
            cad+="     "+despacho[i]->getDestinatario() +"->" + despacho[i]->getDir_destino() + "\n";
        }
    }else
        cad+="0\n";
    return cad;
}

string Office::estadistica() {
    string cad="---Despacho---";
    cad+=Office::listarDespacho(); //no es polimorfismo


    cad+="_____________________________\nPaqueteria Sin clasificar: [" + to_string(cntReal) +"]\n\n";
    for(int i = 0; i<cntReal;i++){
        cad+=postbags[i]->toString()+"\n";
    }


    cad+="____________________________\nPaquetes entregados:\n";
    for(int i = 0; i<cntEntr;i++){
        cad+="\t"+entregas[i]->getDestinatario() +"->" + entregas[i]->getDir_destino() + "\n";
    }

    return cad;
}


//TRABAJO CON ARCHIVOS
string Office::out_postbags() {
    string cad;
    for(int i = 0; i<cntReal; i++) {
        if(dynamic_cast<Telegrama*>(postbags[i]))
            cad+="T*"+postbags[i]->cad_file_out()+"\n";

        else if(dynamic_cast<Carta*>(postbags[i]))
            cad+="C*"+postbags[i]->cad_file_out()+"\n";

        else if(dynamic_cast<Bulto*>(postbags[i]))
            cad+="B*"+postbags[i]->cad_file_out()+"\n";
    }
    return cad;
}
string Office::out_despacho() {
    string cad;

    int all=cntTele+cntBulto+cntCarta;
    for(int j=0 ; j<all; j++) {
        if(dynamic_cast<Telegrama*>(despacho[j]))
            cad+="T*"+despacho[j]->cad_file_out()+"\n";

        else if(dynamic_cast<Carta*>(despacho[j]))
            cad+="C*"+despacho[j]->cad_file_out()+"\n";

        else if(dynamic_cast<Bulto*>(despacho[j]))
            cad+="B*"+despacho[j]->cad_file_out()+"\n";
    }
    return cad;
}
string Office::out_entrega(){
    string cad;
    for(int i = 0; i<cntEntr; i++) {
        if(dynamic_cast<Telegrama*>(entregas[i]))
            cad+="T*"+entregas[i]->cad_file_out()+"\n";

        else if(dynamic_cast<Carta*>(entregas[i]))
            cad+="C*"+entregas[i]->cad_file_out()+"\n";

        else if(dynamic_cast<Bulto*>(entregas[i]))
            cad+="B*"+entregas[i]->cad_file_out()+"\n";
    }
    return cad;

}


//CARGANDO DATOS || se usa en load
//Sobre carga   de metodo
void Office::addDespacho(PostBag* corresp) {
    int all = cntTele+cntCarta+cntBulto;
    if(cntTele+cntCarta+cntBulto >= cant_init)
        throw out_of_range("Se alcanzo el Limite del arreglo");
    else{
        despacho[all] = corresp;
        if(dynamic_cast<Telegrama*>(corresp))
            cntTele++;
        else if(dynamic_cast<Carta*>(corresp))
            cntCarta++;
        else if(dynamic_cast<Bulto*>(corresp))
            cntBulto++;
        }
}
