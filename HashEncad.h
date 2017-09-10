#ifndef HASHENCAD_H
#define HASHENCAD_H

#include "ListaEncad.h"
#include <string>
#include <iostream>
#include "math.h"
#include "GerTexto.h"
#include "Tweet.h"

using namespace std;

class HashEncad{
private:
    ListaEncad* tabela;
    int m, tratColis;
	long long int divisao(long long int chave);
	long long int funcaoH2(long long int chave);
	long long int enlacamento(long long int chave);
    long long int comparacoes;
        
public:
    HashEncad(int tam, int trat);
    void inserir(long long int chave);
    long long int sondLinear(long long int chave);
	long long int sondQuadratica(long long int chave);
    void duploHash(long long int chave);
    void encadSeparado(long long int chave);
    void salvarArquivo(string nome);
    void exibirTabela();        
    ~HashEncad();
};
#endif
