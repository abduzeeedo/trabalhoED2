/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
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
	long int getNumCompar();
	long int getNumCopias();
	double getTempoInsercao();
	double getTempoRemocao();
	double getTempoBusca();
	void limpaDados();
private:
	//variaveis
	No* raiz;
	long int numCompar;
	long int numCopias;
	double tempoGastoInsercao;
	double tempoGastoRemocao;
	double tempoGastoBusca;
	//funcoes
	bool buscaAuxiliar(int tweetId, No* no);
	No* inserirAuxiliar(Tweet* tw, No* no);
	int calculaFB(No* no);
	void imprimirAux(No* no);
	int calculaAltura(No* no);
	void destrutorAux(No* no);
	void setFB(No* no);
	No* removerAux2(No* no);
	No* removerAux(No* no, Tweet* tw);
	No* balanceia(No* no);
	No* rotR(No* no);
	No* rotRR(No* no);
	No* rotL(No* no);
	No* rotLL(No* no);
};
#endif
