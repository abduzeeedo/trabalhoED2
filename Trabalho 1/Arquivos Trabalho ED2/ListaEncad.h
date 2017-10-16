/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef LISTAENCAD_H
#define LESTAENCAD_H

#include <iostream>
#include "No.h"

class ListaEncad
{
  private:
    No* pri;
    No* it;
    ListaEncad* proxLista;
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
