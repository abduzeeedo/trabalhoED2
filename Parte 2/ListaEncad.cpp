#include "ListaEncad.h"

ListaEncad::ListaEncad()
{
    pri = NULL;
    it = NULL;
}
void ListaEncad::addNo(Tweet *chave)
{
    No *n;
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
Tweet *ListaEncad::consultaChave()
{
    return it->atual;
}
Tweet *ListaEncad::retornaPorId(int id)
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
void ListaEncad::inicio()
{
    it = pri;
}
void ListaEncad::proxNo()
{
    if (it != NULL)
        it = it->prox;
}
bool ListaEncad::verificaUlt()
{
    if (it->prox == NULL)
        return true;
    else
        return false;
}
bool ListaEncad::verificaVazio()
{
    if (pri == NULL)
        return true;
    else
        return false;
}
Tweet *ListaEncad::retornaPrimeiro()
{
    return pri->atual;
}
bool ListaEncad::verificaNull()
{
    if (it == NULL)
        return true;
    else
        return false;
}
ListaEncad::~ListaEncad()
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
    delete aux;
}
