#ifndef HASHING_H
#define HASHING_H


#include <string>
#include <iostream>
#include "math.h"

using namespace std;

class Hashing
{
private:
    int m;
    int* table;
    int divisao(int chave);
    int enlacamento(int chave, int hashingFunc);
    void sondLinear(int chave, int hashingFunc);
    void sondQuadratica(int chave, int hashingFunc);
    void duploHash(int chave, int hashingFunc);
    void encadSeparado(int chave, int hashingFunc);
    void encadCol(int chave, int hashingFunc);  
public:
    Hashing(int tamanho);
    void addVetor(int chave, int hashingFunc, int tratColis);
    ~Hashing();
};
#endif
