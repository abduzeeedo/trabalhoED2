#ifndef LZ77_H
#define LZ77_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Tupla.h"
using namespace std;
class LZ77
{
private:
    //variaves
    int tamDic;
    int tamBuffer;
public:
    LZ77(int tamDic, int tamBuffer);
    vector<Tupla*> comprimirPalavra(string palavra);
    string descomprimirPalavra(vector<Tupla*> palavra);
    ~LZ77();
};

#endif
