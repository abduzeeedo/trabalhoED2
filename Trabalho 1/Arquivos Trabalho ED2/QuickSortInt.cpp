/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "QuickSortInt.h"
using namespace std;

//Construtor
QuickSortInt::QuickSortInt()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
QuickSortInt::~QuickSortInt()
{
}

//Retorna o numero de trocas feitas
int QuickSortInt::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int QuickSortInt::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto pela ordenacao
double QuickSortInt::getTempoGasto()
{
	return tempoGasto;
}

void QuickSortInt::limpaDados() {
	numCompar = 0;
	numTrocas = 0;
	tempoGasto = 0;
}

//Funcao que realiza a troca de posicao entre dois inteiros
//ENTRADA: 2 inteiros a serem trocados de posicao entre si
//SAIDA: A troca de posicao entre os dois inteiros
void QuickSortInt::troca(long long int &t1, long long int &t2)
{
	if (t1 != t2) //Nao troca se t1 e t2 sao iguais, ja que nao precisa
	{
		long long int aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}

//Cria vetores de inteiros com tweet ids
//ENTRADA: Vetor de objetos do tipo Tweet e seu tamanho
//SAIDA: Atribuicao dos TweetID`s dos objetos do tipo Tweet's para um vetor de inteiro, e a ordenacao desse vetor de inteiro via QuickSort
void QuickSortInt::criaVet(Tweet* vet[], int tam)
{
	long long int* vetInt = (long long int*)malloc(sizeof(long long int) * tam);
	for (int i = 0; i < tam; i++)
	{
		vetInt[i] = vet[i]->getTweetID();
	}
	quicksortint(vetInt, 0, tam - 1); //Faz a ordenacao do vetor de inteiros criado
}

//Algoritmo de particionamento do vetor
int QuickSortInt::particionaint(long long int vet[], int inicio, int fim)
{
	int pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	long long int pivo = vet[pospiv]; //Coloca o pivo como o meio do vetor
	troca(vet[pospiv], vet[fim]); // Coloca o pivo como o ultimo elemento do vetor
	pospiv = fim; //Volta a posicao do pivo como sendo o fim do vetor que vai ser particionado

				  //Variaveis para percorrer no vetor particionado
	int i = inicio - 1; //Comeca antes do inicio pq na primeira troca ele ja vai virar o inicio
	int j = inicio; //Anda do comeco ate o fim-1 do vetor

	while (j <= fim - 1) //Ele nao vai ate o fim do vetor pois o ultimo elemento eh o pivo que foi jogado para o final no comeco da execucao
	{
		if ((vet[j] <= pivo) && ++numCompar)
		{
			i++;
			troca(vet[i], vet[j]);
		}
		j++;
	}

	troca(vet[i + 1], vet[pospiv]); //Coloca o elemento ja ordenado na ultima posicao do vetor particionado
	return i + 1;
}

//Algoritmo do quicksort recursivo
void QuickSortInt::quicksortint(long long int vet[], int ini, int fim)
{
	clock_t relogio;
	relogio = clock();
	if (ini < fim)
	{
		int part = particionaint(vet, ini, fim);
		quicksortint(vet, ini, part - 1);
		quicksortint(vet, part + 1, fim);
	}
	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}