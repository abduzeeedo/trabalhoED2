#include "Tweet.h"
#include <iostream>
#include <ctime>

class InsertionSort
{
private:
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto; //Contador do tempo gasto na execucao da funcao
public:
	InsertionSort();//Construtor
	~InsertionSort();//Destrutor
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
	void insertionsort(Tweet* vetor[], int inicio, int fim);//Funcao de Ordenacao por InsertionSort
	void limpaDados();
};
