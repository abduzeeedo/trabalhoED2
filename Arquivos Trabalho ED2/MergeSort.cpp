/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "MergeSort.h"

//Construtor
MergeSort::MergeSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
MergeSort::~MergeSort()
{
}

//Retorna o numero de trocas feitas
int MergeSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int MergeSort::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto pela ordenacao
double MergeSort::getTempoGasto()
{
	return tempoGasto;
}

//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
void MergeSort::limpaDados()
{
	numCompar = 0;
	numTrocas = 0;
	tempoGasto = 0;
}

//Funcao que "junta" subparticoes do vetor de tweets
void MergeSort::intercala(Tweet *vet[], int ini, int meio, int fim)
{
	Tweet ** vetAux = (Tweet**)malloc(sizeof(Tweet*) * (fim - ini + 1)); //Aloca um vetor auxiliar para ordenacao
	int posAux = 0; //Variavel para controlar a posicao no vetor auxiliar
	int i = ini; //Comeco do vetor particionado
	int j = meio + 1; //Fim do vetor particionado. (O fim recebido por parametro eh o fim do vetor original)

	while (i < meio + 1 && j < fim + 1)
	{
		if ((vet[i]->getTweetID() > vet[j]->getTweetID()) && ++numCompar)
		{
			vetAux[posAux] = vet[j];
			j++;
			numTrocas++;
		}
		else
		{
			vetAux[posAux] = vet[i];
			i++;
			numTrocas++;
		}
		posAux++;
	}
	//Pega posicoes ordenadas na primeira metade do vetor para juntar
	while (i < meio + 1)
		vetAux[posAux++] = vet[i++];
	//Pega posicoes ordenadas na segunda metade do vetor para juntar
	while (j < fim + 1)
		vetAux[posAux++] = vet[j++];
	//Passa o vetor auxiliar ordenado para o vetor original
	for (int f = 0; f < (fim - ini + 1); f++)
		vet[ini + f] = vetAux[f];
	//Desaloca o vetor auxiliar
	free(vetAux);
}

//Funcao de ordenacao por MergeSort Recursivo
void MergeSort::mergesort(Tweet *vet[], int inicio, int fim)
{
	clock_t relogio;
	relogio = clock();
	if (inicio < fim)
	{
		int meio = (inicio + fim) / 2;
		//Chama a funcao recursivamente para as duas metades do vetor
		mergesort(vet, inicio, meio);
		mergesort(vet, meio + 1, fim);
		//Intercala as duas metades ordenadas
		intercala(vet, inicio, meio, fim);
	}
	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}