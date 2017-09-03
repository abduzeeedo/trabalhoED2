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
    int enlacamento(int chave);
public:
    Hashing(int tamanho);
    void addVetor(int chave, int hashingFunc, int tratColis);
    ~Hashing();
};
#endif
