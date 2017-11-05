/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef ARVORESPLAY_H
#define ARVORESPLAY_H

#include <iostream>
#include <ctime>
#include "stdlib.h"
#include "Tweet.h"

class ArvoreSplay
{
private:
	long int numCompar; //Numero de comparacoes feitas
	long int numCopias; //Numero de copias de registro feitas
	double tempoGastoInsercao; //Tempo gasto nas insercoes (somado a cada insercao)
	double tempoGastoRemocao; //Tempo gasto nas remocoes (calculado a cada remocao)
	struct No* raiz; //Raiz da arvore
	struct No* rotacaoDir(No*); //Rotacao a direita
	struct No* rotacaoEsq(No*); //Rotacao a esquerda
	struct No* splay(No*, Tweet*); //Funcao de espalhamento
	struct No* addNo(Tweet*); //Funcao auxiliar de insercao
	void deletaArvore(No*); //Funcao auxiliar para o destrutor
public:
	ArvoreSplay();
	~ArvoreSplay();
	struct No* getRaiz(); //Retorna a raiz da arvore
	long int getnumCompar(); //Retorna o numero de comparacoes feitas
	long int getnumCopias(); //Retorna o numero de copias de registro feitas
	double gettempoInsercao(); //Retorna o tempo gasto nas insercoes
	double gettempoRemocao(); //Retorna o tempo gasto na remocao
	struct No* busca(Tweet*); //Funcao de busca
	struct No* insereNo(Tweet*); //Funcao de insercao
	struct No* removeNo(Tweet*); //Funcao de remocao
	void imprimeArvore(No*); //Imprime a arvore
};
#endif
