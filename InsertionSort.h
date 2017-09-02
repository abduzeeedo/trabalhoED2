#include "tweets.h"
#include <iostream>
#include <ctime>

class InsertionSort
{
private:
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	InsertionSort();
	~InsertionSort();
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
	void insertionsort(tweets* vetor[], int tam);
};