#ifndef PALAVRA_H
#define PALAVRA_H
#include <string>
using namespace std;

class Palavra
{
    private:
        string conteudo;
        int frequencia;
        int numero_hash;
    public:
        Palavra();
        Palavra (string,int);
        virtual ~Palavra();
        string getConteudo();
        void setConteudo(string);
        int getFreq();
        void setFreq(int);
        void aumentaFreq();
        void setHash(int);
        int getHash();
};

#endif // PALAVRA_H
