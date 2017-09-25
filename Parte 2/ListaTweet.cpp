/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

#include "ListaTweet.h"

ListaTweet::ListaTweet()
{
    pri = NULL;
    it = NULL;
}
void ListaTweet::addNo(Tweet *chave)
{
    No *n = new No;
    n->atual = chave;
    n->prox = NULL;
    if (pri == NULL)
        pri = n;
    else
    {
        it = pri;
        while (it->prox != NULL)
        {
            it = it->prox;
        }
        it->prox = n;
    }
}
Tweet *ListaTweet::consultaChave()
{
    return it->atual;
}
Tweet *ListaTweet::retornaPorId(int id)
{
    if (!verificaVazio())
    {
        inicio();
        while (it != NULL)
        {
            if (it->atual->getTweetID() == id)
            {
                return it->atual;
                break;
            }
            else
                it = it->prox;
        }
        if (it == NULL)
            return NULL;
    }
}
void ListaTweet::inicio()
{
    it = pri;
}
void ListaTweet::proxNo()
{
    if (it != NULL)
        it = it->prox;
}
bool ListaTweet::verificaUlt()
{
    if (it->prox == NULL)
        return true;
    else
        return false;
}
bool ListaTweet::verificaVazio()
{
    if (pri == NULL)
        return true;
    else
        return false;
}
Tweet *ListaTweet::retornaPrimeiro()
{
    return pri->atual;
}
bool ListaTweet::verificaNull()
{
    if (it == NULL)
        return true;
    else
        return false;
}
ListaTweet::~ListaTweet()
{
    it = pri;
    No *aux;
    while (it->prox != NULL)
    {
        aux = it->prox;
        delete it;
        it = aux;
    }
    delete it;
    //delete aux;
}
