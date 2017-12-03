#ifndef TUPLA_H
#define TUPLA_H


class Tupla
{
    public:
        Tupla();
        virtual ~Tupla();
        void setP(int p);
        void setL(int l);
        void setC(char c);
        int getP();
        int getL();
        char getC();
    protected:

    private:
         int p; //posicao relativa da maior sequencia do dicionario
        int l; //comprimento da maior sequencia
        char c; //simbolo do buffer que segue a sequencia
};

#endif // TUPLA_H
