/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Tweet.h"
#include <iostream>
#include <ctime>

class QuickSortInt
{
private:
	int particionaint(long long int vetor[], int inicio, int fim); //Funcao que particiona um vetor de inteiros realiza as torcas necessarias
	void quicksortint(long long int vetor[], int ini, int fim);//Funcao de ordenacao por QuickSort Recursivo em um vetor de inteiros
	void troca(long long int &t1, long long int &t2);//Realiza a troca de posicao entre 2 inteiros passados por parametro
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto;//Contador do tempo gasto na execucao da funcao
public:
	QuickSortInt();//Construtor
	~QuickSortInt();//Destrutor
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
	void criaVet(Tweet* vet[], int tam);//Insere os tweetID`s de um vetor de objetos do tipo Tweet em um vetor de inteiros
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
};