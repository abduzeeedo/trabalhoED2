#ifndef HASHTWEET_H
#define HASHTWEET_H

#include "ListaEncad.h"
#include <string>
#include <iostream>
#include "math.h"
#include "GerTexto.h"
#include "Tweet.h"
#include <stdlib.h>
#include <sstream>

using namespace std;

class HashTweet{
private:
    ListaEncad* tabela;
    int m, tratColis;
	long long int divisao(long long int chave);
	long long int enlacamento(long long int chave);
    long long int comparacoes;
    long long int maiorPrimo(int N);


public:
    HashTweet(int tam, int trat);
    void inserir(Tweet* chave);
    void encadSeparado(Tweet* chave);
    Tweet* retornaPorTweetId(int id);
    Tweet* retornaPorPosicao(int id);
    void salvarArquivo(string nome);
    void exibirTabela();
    ~HashTweet();
};
#endif
