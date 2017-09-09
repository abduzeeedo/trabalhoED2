#include "Tweet.h"
#include <iostream>
#include <ctime>

class QuickSort
{
private:
	int particiona(Tweet* vetor[], int inicio, int fim, int pos); //Funcao que particiona um vetor de tweets utilizando um pivo passado por parametro e realiza as torcas necessarias
	int mediana(Tweet* vet[], int numVal, int inicio, int fim);//Funcao que calcula a mediana entre 3 e 5 valores de TweetID's e retorna a posicao de tal valor
	void troca(Tweet* &t1, Tweet* &t2);//Realiza a troca de posicao entre 2 objetos do tipo tweet passados por parametro
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto;//Contador do tempo gasto na execucao da funcao
public:
	QuickSort();//Construtor
	~QuickSort();//Destrutor
	void quicksort(Tweet* vetor[], int ini, int fim, char tipo);//Funcao de ordenacao por QuickSort Recursivo e suas variacoes
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto

};
