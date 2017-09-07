#include "Tweet.h"
#include <iostream>
#include <ctime>

class QuickSort
{
private:
	int particiona(Tweet* vetor[], int inicio, int fim, int pos);
	int mediana(Tweet* vet[], int numVal, int inicio, int fim);
	void troca(Tweet* &t1, Tweet* &t2);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	QuickSort();
	~QuickSort();
	void quicksort(Tweet* vetor[], int ini, int fim, char tipo);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();

};
