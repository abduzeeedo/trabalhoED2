#ifndef HASHPALAVRA_H
#define HASHPALAVRA_H

#include <string>
#include "ListaPalavra.h"
#include "Palavra.h"
#include <sstream>
#include "math.h"
#include <vector>
#include "GerTexto.h"
using namespace std;

class HashPalavra
{
private:
    ListaPalavra* tabela;
    int m;
    long long int maiorPrimo(int N);
    long long int funcaoHashing(string chave);
    void encadSeparado(Palavra* chave);
public:
    void inserir(Palavra* p);
    void salvarArquivo(string nome);
    Palavra* retornaPorPalavra(string id);
    Palavra* retornaPorPosicao(int id);
    void exibirTabela();
    vector<Palavra> retornaVetor();
    HashPalavra(int tam);
    ~HashPalavra();

};


#endif
