
#include "HeapSort.h"

using namespace std;

//Construtor
HeapSort::HeapSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
HeapSort::~HeapSort()
{
}

//Retorna o numero de trocas feitas
int HeapSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int HeapSort::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto
double HeapSort::getTempoGasto()
{
	return tempoGasto;
}

void HeapSort::limpaDados() {
	numCompar = 0;
	numTrocas = 0;
	tempoGasto = 0;
}

//Constroi um vetor Heap
void HeapSort::constroiHeap(Tweet* vetor[], int tam, int indice_raiz)
{
	int ramificacao;
	Tweet* valor;
	valor = vetor[indice_raiz];

	while (indice_raiz < tam / 2) {
		ramificacao = 2 * indice_raiz + 1;

		if (ramificacao < tam - 1 && vetor[ramificacao]->getTweetID() < vetor[ramificacao + 1]->getTweetID()) {
			ramificacao++;

		}
		if (valor->getTweetID() >= vetor[ramificacao]->getTweetID()) {//Identifica o max-heap
			numTrocas++;
			break;
		}

		vetor[indice_raiz] = vetor[ramificacao];
		indice_raiz = ramificacao;
		++numCompar;
	}
	vetor[indice_raiz] = valor;
}




//Realiza as trocas
void HeapSort::heapsort(Tweet* vetor[], int tam)
{
	clock_t relogio;
	relogio = clock();

	int indice;
	Tweet* troca;
	for (indice = tam / 2; indice >= 0; indice--)
		constroiHeap(vetor, tam, indice);

	while (tam > 0)
	{
		troca = vetor[0];
		vetor[0] = vetor[tam - 1];
		vetor[tam - 1] = troca;
		numTrocas++;
		constroiHeap(vetor, --tam, 0);
	}

	tempoGasto = (clock() - relogio) / (double)CLOCKS_PER_SEC;

}

