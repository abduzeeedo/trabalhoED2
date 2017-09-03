#include "tweets.h"
#include <iostream>
#include <ctime>

class QuickSort
{
private:
	int particiona(tweets* vetor[], int inicio, int fim);
	int particionaMediana(tweets* vetor[], int inicio, int fim);
	int mediana(tweets* vet[], int numVal, int inicio, int fim);
	void troca(tweets* &t1, tweets* &t2);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	QuickSort();
	~QuickSort();
	void quicksort(tweets* vetor[], int ini, int fim, char tipo);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();

};