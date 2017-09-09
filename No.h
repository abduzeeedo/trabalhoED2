#ifndef NO_H
#define NO_H

#include <iostream>
#include "ListaEncad.h"

using namespace std;
class No
{
  private:
    int chave;
    No *prox;

  public:
    No(int id);
    void setProx(No *proximo);
    int getChave();
    No* getProx();
    ~No();
};
#endif