#include "Tweet.h"
#include <iostream>
#include <ctime>

class BubbleSort
{
private:
	void troca(Tweet* &t1, Tweet* &t2);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	BubbleSort();
	~BubbleSort();
	void bubblesort(Tweet* vetor[], int tam);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
};

