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

double QuickSortInt::getTempoGasto()
{
	return tempoGasto;
}

//Nao usei o std::swap para poder adicionar o de numero de trocas
void QuickSortInt::troca(int &t1, int &t2)
{
	if (t1 != t2) //Nao troca se t1 e t2 sao iguais, ja que nao precisa
	{
		int aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}

//Cria vetores de inteiros com tweet ids
void QuickSortInt::criaVet(Tweet* vet[], int tam)
{
	int* vetInt = (int*)alloca(sizeof(int) * tam); //Melhor que malloc pois ja desaloca a memoria automaticamente quando sai da funcao
	for (int i = 0; i < tam; i++)
	{
		vetInt[i] = vet[i]->getTweetID();
	}
	quicksortint(vetInt, 0, tam-1); //Faz a ordenacao do vetor de inteiros criado
	//Imprime o vetor ordenado
	cout << "Depois de Ordenar:" << endl;
	cout << "Vetor: ";
		for (int k = 0; k < tam; k++)
		{
			cout << "[" << vetInt[k] << "]";
		}
}

//Algoritmo de particionamento do vetor
int QuickSortInt::particionaint(int vet[], int inicio, int fim)
{
	int pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	int pivo = vet[pospiv]; //Coloca o pivo como o meio do vetor
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
void QuickSortInt::quicksortint(int vet[], int ini, int fim)
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