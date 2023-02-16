#ifndef BULTO_H
#define BULTO_H

#include <PostBag.h>


class Bulto : public PostBag
{
    public:
        Bulto(string, string, string,int,int,int,float,int);
        string toString() override;
        string cad_file_out() override;
        float calcPrice();
        virtual ~Bulto();

    private:
        float peso;
        int urgencia; // 1-Urgente, 2- medio, 3- indiferente
};

#endif // BULTO_H
