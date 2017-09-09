#include "Tweet.h"
#include <iostream>
#include <ctime>

class MergeSort
{
private:
	void intercala(Tweet* vetor[], int inicio, int meio, int fim);//Funcao que "junta" subparticoes do vetor de tweets
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto;//Contador do tempo gasto na execucao da funcao
public:
	MergeSort();//Construtor
	~MergeSort();//Destrutor
	void limpaDados();
	void mergesort(Tweet* vetor[], int inicio, int fim);//Funcao de ordenacao por MergeSort Recursivo
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
};

