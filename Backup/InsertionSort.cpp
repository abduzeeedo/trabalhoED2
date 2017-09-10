#include "InsertionSort.h"
using namespace std;

//Construtor
InsertionSort::InsertionSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
InsertionSort::~InsertionSort()
{
}

//Retorna o numero de trocas feitas
int InsertionSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int InsertionSort::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto pela ordenacao
double InsertionSort::getTempoGasto()
{
	return tempoGasto;
}

void InsertionSort::limpaDados()
{
	numCompar = 0;
	numTrocas = 0;
	tempoGasto = 0;
}

//Algoritmo InsertionSort
//ENTRADA: Vetor de objetos do tipo Tweet, a posicao inicial e final do intervalo a ser ordenado
//SAIDA: Tal vetor ordenado via InsertionSort
void InsertionSort::insertionsort(Tweet* vet[], int inicio, int fim)
{
	clock_t relogio;
	relogio = clock();//Instancia um novo contador de tempo

	int i, j;
	Tweet* chave; //chave auxiliar

	for (i = inicio + 1; i < fim; i++) //comeca da posicao inicio e termina na posicao fim
	{
		chave = vet[i]; //salva o valor atual do vet[i] na chave auxiliar
		j = i - 1;

		/* Desloca os elementos anteriores a chave que sao maiores que ela 1 posicao a frente da sua posicao atual*/
		while (j >= 0 && (vet[j]->getTweetID() > chave->getTweetID()) && ++numCompar)
		{
			vet[j + 1] = vet[j];
			numTrocas++;
			j--;
		}
		vet[j + 1] = chave; //coloca o valor salvo da chave na posicao que "sobrou" antes dos valores maiores que a chave
		numTrocas++;
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}