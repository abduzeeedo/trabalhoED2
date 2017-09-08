#include "Tweet.h"
#include <iostream>
#include <ctime>

class QuickSortInt
{
private:
	int particionaint(long long int vetor[], int inicio, int fim);
	void quicksortint(long long int vetor[], int ini, int fim);
	void troca(long long int &t1, long long int &t2);
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