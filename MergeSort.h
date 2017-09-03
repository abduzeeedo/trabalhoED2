#include "tweets.h"
#include <iostream>
#include <ctime>

class MergeSort
{
private:
	void intercala(tweets* vetor[], int inicio, int meio, int fim);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	MergeSort();
	~MergeSort();
	void mergesort(tweets* vetor[], int inicio, int fim);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
};

