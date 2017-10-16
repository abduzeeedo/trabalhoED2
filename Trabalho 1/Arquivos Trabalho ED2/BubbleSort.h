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

class BubbleSort
{
private:
	void troca(Tweet* &t1, Tweet* &t2);//Realiza a troca de posicao entre 2 objetos do tipo tweet passados por parametro
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto;//Contador do tempo gasto na execucao da funcao
public:
	BubbleSort();//Construtor
	~BubbleSort();//Destrutor
	void bubblesort(Tweet* vetor[], int tam);//Funcao de ordenacao por BubbleSort
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
};
