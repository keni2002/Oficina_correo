#ifndef TELEGRAMA_H
#define TELEGRAMA_H

#include <PostBag.h>


class Telegrama : public PostBag //inherit
{
    public:

        Telegrama(string,string,string,int,int,int,int,float);
        string toString() override;
        string cad_file_out() override;
        int getCntWords();
        float calcPrice();
        virtual ~Telegrama();

    private:
        int cntWords;//cantidad palabras
        float impuesto; //impuesto aplicado
};

#endif // TELEGRAMA_H
