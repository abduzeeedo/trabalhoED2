#include "No.h"
No::No()
{
    chave = NULL;
    fatorBalanceamento = 0;
    esq = NULL;
    dir = NULL;
}
 No::~No()
{
    delete chave;
}
No* No::getEsq()
{
    return esq;
}

No* No::getDir()
{
    return dir;
}

int No::getFB()
{
    return fatorBalanceamento;
}

Tweet* No::getChave()
{
    return chave;
}

void No::setEsq(No* esq)
{
    this->esq = esq;
}

void No::setDir(No* dir)
{
    this->dir = dir;
}

void No::setFB(int fb)
{
    fatorBalanceamento = fb;
}

void No::setChave(Tweet* chave)
{
    this->chave = chave;
}
