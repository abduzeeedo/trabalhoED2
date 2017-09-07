#include "MergeSort.h"

MergeSort::MergeSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

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

void MergeSort::intercala(Tweet *vet[], int ini, int meio, int fim)
{
	Tweet ** vetAux = (Tweet**)malloc(sizeof(Tweet*) * (fim - ini + 1)); //Aloca um vetor auxiliar para ordena�ao
	int posAux = 0; //Variavel para controlar a posi�ao no vetor auxiliar
	int i = ini; //Come�o do vetor particionado
	int j = meio + 1; //Fim do vetor particionado. (O fim recebido por parametro � o fim do vetor original)

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

void MergeSort::mergesort(Tweet *array[], int inicio, int fim)
{
	clock_t relogio;
	relogio = clock();
	if (inicio < fim)
	{
		int meio = (inicio + fim) / 2;
		//Chama a fun�ao recursivamente para as duas metades do vetor
		mergesort(array, inicio, meio);
		mergesort(array, meio + 1, fim);
		//Intercala as duas metades ordenadas
		intercala(array, inicio, meio, fim);
	}
	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}