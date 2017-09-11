/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "No.h"

No::No(int id)
{
    chave = id;
    prox = NULL;
}
No::~No()
{
}
void No::setProx(No *proximo)
{
    prox = proximo;
}
int No::getChave()
{
    return chave;
}
No* No::getProx()
{
    return prox;
}
