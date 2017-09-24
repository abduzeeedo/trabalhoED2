#ifndef LISTAENCAD_H
#define LESTAENCAD_H

#include <iostream>
#include "Tweet.h"

typedef struct No
{
  Tweet *atual;
  No *prox;
} No;
class ListaEncad
{
private:
  No *pri;
  No *it;

public:
  ListaEncad();
  ~ListaEncad();
  void addNo(Tweet* tw);
  Tweet *consultaChave();
  Tweet* retornaPrimeiro();
  Tweet *retornaPorId(int id);
  void inicio();
  void proxNo();
  bool verificaUlt();
  bool verificaVazio();
  bool verificaNull();
};
#endif
