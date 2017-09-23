/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Palavra.h"
#include <iostream>
#include <ctime>
#include <vector>

class MergeSort
{
private:
	void intercala(vector<Palavra> &vPal, int inicio, int meio, int fim);//Funcao que "junta" subparticoes do vetor de tweets
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
public:
	MergeSort();//Construtor
	~MergeSort();//Destrutor
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
	void mergesort(vector<Palavra> &vPal, int inicio, int fim);//Funcao de ordenacao por MergeSort Recursivo
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
};
