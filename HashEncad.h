#ifndef HASHENCAD_H
#define HASHENCAD_H

#include "ListaEncad.h"
#include <string>
#include <iostream>
#include "math.h"
#include "GerTexto.h"

using namespace std;

class HashEncad{
private:
    ListaEncad* tabela;
    int m, tratColis;
    int divisao(int chave);
    int funcaoH2(int chave);
    int enlacamento(int chave); 
    long long int comparacoes;
    
    
public:
    HashEncad(int tam, int trat);
    void inserir(int chave);
    int sondLinear(int chave);
    int sondQuadratica(int chave);
    void duploHash(int chave);
    void encadSeparado(int chave);
    void salvarArquivo(string nome);
    void exibirTabela();        
    ~HashEncad();
};
#endif
