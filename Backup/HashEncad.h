#ifndef HASHENCAD_H
#define HASHENCAD_H

#include "ListaEncad.h"
#include <string>
#include <iostream>
#include "GerTexto.h"

using namespace std;

class HashEncad {
private:
	ListaEncad* tabela;
	int m;
	int divisao(int chave);
	int enlacamento(int chave);

public:
	HashEncad(int tam);
	void inserir(int chave, int tratColis);
	int sondLinear(int chave);
	int sondQuadratica(int chave);
	void duploHash(int chave);
	void encadSeparado(int chave);
	void salvarArquivo(string nome);
	void exibirTabela();
	~HashEncad();
};
#endif
