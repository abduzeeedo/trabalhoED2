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
