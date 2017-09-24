#include "ListaPalavra.h"

ListaPalavra::ListaPalavra()
{
    pri = NULL;
    it = NULL;
}
/*
    Adiciona uma nova palavra na lista
    se a palavra já existe ele vai incrementar a frequencia
*/
void ListaPalavra::addNo(Palavra *chave)
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
            if(it->atual->getConteudo() == n->atual->getConteudo())
                {
                    it->atual->aumentaFreq();
                    break;
                }
            it = it->prox;
        }
        if(it->prox==NULL && it->atual->getConteudo()!= n->atual->getConteudo())
        it->prox = n;
    }
}
//retorna a palavra da posicao do ponteiro
Palavra *ListaPalavra::consultaChave()
{
    return it->atual;
}
// Retorna a palavra do id desejado
Palavra *ListaPalavra::retornaPorId(string id)
{
    if (!verificaVazio())
    {
        inicio();
        while (it != NULL)
        {
            if (it->atual->getConteudo() == id)
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
//volta para o inicio da lista
void ListaPalavra::inicio()
{
    it = pri;
}
//avanca para o proximo nó
void ListaPalavra::proxNo()
{
    if (it != NULL)
        it = it->prox;
}
//verifica se está no ultimo nó
bool ListaPalavra::verificaUlt()
{
    if (it->prox == NULL)
        return true;
    else
        return false;
}
//verifica se a lista está vazia
bool ListaPalavra::verificaVazio()
{
    if (pri == NULL)
        return true;
    else
        return false;
}
//retorna a palavra do primeiro nó
Palavra *ListaPalavra::retornaPrimeiro()
{
    return pri->atual;
}
//verifica se o it está em uma posicao nula
bool ListaPalavra::verificaNull()
{
    if (it == NULL)
        return true;
    else
        return false;
}
//destrutor
ListaPalavra::~ListaPalavra()
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
