#ifndef LZ77_H
#define LZ77_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class LZ77
{
    typedef struct Tripla
    {
        int p; //posicao relativa da maior sequencia do dicionario
        int l; //comprimento da maior sequencia
        char c; //simbolo do buffer que segue a sequencia
    } Tripla;
private:
    //variaves
    int tamDic;
    int tamBuffer;
    char* buffer;
    char* dicionario;
    //funcoes
    void limpaDicionario();
    void LimpaBuffer();
public:
    LZ77();
    string comprimirPalavra(string palavra);
    string descomprimirPalavra(string palavra);

    ~LZ77();
};

#endif
