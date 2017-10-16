/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

#ifndef HASHTWEET_H
#define HASHTWEET_H

#include "ListaTweet.h"
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
    ListaTweet* tabela;
    int m;
	long long int divisao(long long int chave);
	long long int enlacamento(long long int chave);
    long long int comparacoes;
    long long int maiorPrimo(int N);
    void encadSeparado(Tweet* chave);


public:
    HashTweet(int tam);
    void inserir(Tweet* chave);
    Tweet* retornaPorTweetId(int id);
    Tweet* retornaPorPosicao(int id);
    void salvarArquivo(string nome);
    void exibirTabela();
    ~HashTweet();
};
#endif
