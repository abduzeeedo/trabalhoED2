#ifndef HASHSTRUCT_H
#define HASHSTRUCT_H

#include <string>
#include <iostream>
#include "math.h"
#include "GerTexto.h"

using namespace std;
typedef struct lista
{
	long long int chave;
   int prox;
  bool posVazia;
} lista;

class HashStruct
{
private:
  lista *tabela;
  int m;
  long long int comparacoes;  
  long long int enlacamento(long long int chave);
  long long int divisao(long long int chave);
  void encadCol(long long int chave);


public:
  HashStruct(int tam);
  void inserir(long long int chave);
  void exibirTabela();
  void salvarArquivo(string nome);
  ~HashStruct();
};
#endif