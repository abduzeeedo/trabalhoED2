#ifndef LISTAENCAD_H
#define LESTAENCAD_H

#include <iostream>
#include "No.h"
class ListaEncad
{
  private:
    No* pri;
    No* it;
  public:
    ListaEncad();
    ~ListaEncad();
    void addNo(int val);
    int consultaChave();
    void inicio();
    void proxNo();
    bool verificaUlt();
    bool verificaVazio();
    bool verificaNull();
    
};
#endif
