#include "ListaEncad.h"

ListaEncad::ListaEncad()
{
    pri = NULL;
    it = NULL;
}
void ListaEncad::addNo(int val)
{
    No *n = new No(val);
    if (pri == NULL)
        pri = n;
    else
    {
        it = pri;
        while (it->getProx() != NULL)
        {
            it = it->getProx();
        }
        it->setProx(n);
    }
}
int ListaEncad::consultaChave()
{
    return it->getChave();
}
void ListaEncad::inicio()
{
    it = pri;
}
void ListaEncad::proxNo()
{
    if (it!= NULL)
        it = it->getProx();
}
bool ListaEncad::verificaUlt()
{
    if (it->getProx() == NULL)
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
bool ListaEncad::verificaNull(){
    if(it == NULL)
        return true;
    else return false;
}
ListaEncad::~ListaEncad()
{
    it = pri;
    No *aux;
    while (it->getProx() != NULL)
    {
        aux = it->getProx();
        delete it;
        it = aux;
    }
    delete it;
    delete aux;
}
