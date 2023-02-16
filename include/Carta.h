#ifndef CARTA_H
#define CARTA_H

#include "PostBag.h"
#include "Fecha.h"

class Carta : public PostBag
{
    public:
        Carta(string,string,string,int,int,int,bool);
        virtual ~Carta();
        string toString() override;
        string cad_file_out() override;
        float calcPrice();

    private:

        bool esExterior;//es de otro pais?


};

#endif // CARTA_H
