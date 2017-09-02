#include "tweets.h"
#include <iostream>
#include <ctime>

class BubbleSort
{
private:
	void troca(tweets* &t1, tweets* &t2);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	BubbleSort();
	~BubbleSort();
	void bubblesort(tweets* vetor[], int tam);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
};

