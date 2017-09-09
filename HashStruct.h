#ifndef HASHSTRUCT_H
#define HASHSTRUCT_H

#include <string>
#include <iostream>
#include "math.h"
#include "GerTexto.h"

using namespace std;
typedef struct lista
{
   int chave;
   int prox;
  bool posVazia;
} lista;

class HashStruct
{
private:
  lista *tabela;
  int m;
  int enlacamento(int chave);
  void encadCol(int chave);

public:
  HashStruct(int tam);
  void inserir(int chave);
  void exibirTabela();
  void salvarArquivo(string nome);
  ~HashStruct();
};
#endif