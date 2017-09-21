#ifndef PALAVRA_H
#define PALAVRA_H
#include <string>
using namespace std;

class Palavra
{
    private:
        string conteudo;
        int frequencia;
    public:
        Palavra();
        Palavra (string,int);
        virtual ~Palavra();
        string getConteudo();
        void setConteudo(string);
        int getFreq();
        void setFreq(int);
        void aumentaFreq();
};

#endif // PALAVRA_H
