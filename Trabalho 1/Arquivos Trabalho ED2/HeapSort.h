/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Tweet.h"
#include <iostream>
#include <ctime>

class HeapSort
{
private:
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	HeapSort();
	~HeapSort();
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
	void limpaDados();
	void heapsort(Tweet* vetor[], int tam);
	void constroiHeap(Tweet* vetor[], int tam, int indice_raiz);

};
