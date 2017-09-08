#include "Tweet.h"
#include <iostream>
#include <ctime>

class QuickSortInt
{
private:
	int particionaint(int vetor[], int inicio, int fim);
	void quicksortint(int vetor[], int ini, int fim);
	void troca(int &t1, int &t2);
	int numTrocas;
	int numCompar;
	double tempoGasto;
public:
	QuickSortInt();
	~QuickSortInt();
	void criaVet(Tweet* vet[],int tam);
	int getNumTrocas();
	int getNumComparacoes();
	double getTempoGasto();
};