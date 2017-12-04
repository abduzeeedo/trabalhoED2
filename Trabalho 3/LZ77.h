/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef LZ77_H
#define LZ77_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include "Tupla.h"
using namespace std;
class LZ77
{
private:
    //variaves
    int tamDic;
    int tamBuffer;
    double tempoGasto;
public:
    LZ77(int tamDic, int tamBuffer);
    vector<Tupla*> comprimirPalavra(string palavra);
    string descomprimirPalavra(vector<Tupla*> palavra);
    string tuplaToString(vector<Tupla*> palavra);
    void salvaArquivo(vector<Tupla*> palavra, string nomeArquivo);
    double getTempoGasto();
    ~LZ77();
};

#endif
