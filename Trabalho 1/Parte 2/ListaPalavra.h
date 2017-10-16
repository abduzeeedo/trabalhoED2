/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

#ifndef LISTAPALAVRA_H
#define LISTAPALAVRA_H

#include <iostream>
#include "Palavra.h"
#include <string>
//struct do nó


class ListaPalavra
{

private:
    typedef struct No
    {
        Palavra *atual;
        No *prox;
    } No;
    No *pri;
    No *it;

public:
    ListaPalavra();
    ~ListaPalavra();
    void addNo(Palavra* p);
    Palavra *consultaChave();
    Palavra* retornaPrimeiro();
    Palavra* retornaPorId(string id);
    void inicio();
    void proxNo();
    bool verificaUlt();
    bool verificaVazio();
    bool verificaNull();
};
#endif
