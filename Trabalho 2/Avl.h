#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <ctime>
#include "Tweet.h"
#include "No.h"
using namespace std;
class AVL
{
public:
    AVL();
    virtual ~AVL();
    bool busca(int tweetId);
    void inserir(Tweet* tw);
    void remover(Tweet* tw);
    void imprimir();
private:
    //variaveis
    No* raiz;
    long int numCompar;
    long int numCopias;
    double tempoGastoInsercao;
    double tempoGastoRemocao;
    //funcoes
    bool buscaAuxiliar(int tweetId, No* no);
    void inserirAuxiliar(Tweet* tw, No* no);
    void calculaFB(No* no);
    void imprimirAux(No* no);
    int calculaAltura(No* no);
    void destrutorAux(No* no);
    No* removerAux2(No* no);
    No* removerAux(No* no, Tweet* tw);
    No* balanceia(No* no);
    No* rotR(No* no);
    No* rotRR(No* no);
    No* rotL(No* no);
    No* rotLL(No* no);
    long int getNumCompar();
    long int getNumCompias();
    double getTempoInsercao();
    double getTempoRemocao();


};
#endif
