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
  long long int comparacoes;  
  int enlacamento(int chave);
  int divisao(int chave);
  void encadCol(int chave);


public:
  HashStruct(int tam);
  void inserir(int chave);
  void exibirTabela();
  void salvarArquivo(string nome);
  ~HashStruct();
};
#endif