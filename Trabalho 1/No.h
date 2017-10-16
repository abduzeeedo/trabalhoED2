#ifndef NO_H
#define NO_H

#include <iostream>

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