/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "No_VP.h"
#include "Tweet.h"
#include <ctime>

#ifndef ArvoreVP_H
#define ArvoreVP_H

class ArvoreVP
{
public:
	ArvoreVP();
	void insere(long long int valor);
	void remover(long long int p);
	int alturaVP();
	No_VP** getRaiz();
	long int getNumCompar(); //Retorna o numero de comparacoes feitas
	long int getNumCopias(); //Retorna o numero de copias de registro feitas
	double getTempoInsercao(); //Retorna o tempo gasto nas insercoes
	double getTempoRemocao(); //Retorna o tempo gasto na remocao
	void limpaDados();
	~ArvoreVP();

private:
	No_VP* raiz;
	void insereAVP(No_VP* no, No_VP* pai, long long int valor);
	void deletaH(No_VP* p);
	void corrigeCaso1(No_VP* no);
	void corrigeCaso2(No_VP* no);
	void corrigeCaso3(No_VP* no);
	void corrigeCaso4(No_VP* no);
	void corrigeCaso5(No_VP* no);
	void rotacaoEsquerda(No_VP* no);
	void rotacaoDireita(No_VP* no);
	void removerCaso1(No_VP* n);
	void removerCaso2(No_VP* n);
	void removerCaso3(No_VP* n);
	void removerCaso4(No_VP* n);
	void removerCaso5(No_VP* n);
	void removerCaso6(No_VP* n);
	No_VP* getPredecessor(No_VP* no);
	No_VP* getIrmao(No_VP* no);
	void trocaNos(No_VP* noVelho, No_VP* noNovo);
	int altura(No_VP* no);
	long int numCompar; //Numero de comparacoes feitas
	long int numCopias; //Numero de copias de registro feitas
	double tempoGastoInsercao; //Tempo gasto nas insercoes (somado a cada insercao)
	double tempoGastoRemocao; //Tempo gasto nas remocoes (calculado a cada remocao)
};

#endif // ArvoreVermelhoPreta_H
#pragma once