#include "QuickSort.h"
using namespace std;

/*
ainda falta:
escrever mais comentarios
implementar a funcao para ler do arquivo entrada.txt para fazer a ordenaçao aleatoria dos tweets
implementar a funcao para escrever os resultados no arquivo saida.txt
alterar o codigo para funcionar no numero N de vezes lidos da entrada.txt
*/

//Construtor
QuickSort::QuickSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
QuickSort::~QuickSort()
{
}

//Retorna o numero de trocas feitas
int QuickSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int QuickSort::getNumComparacoes()
{
	return numCompar;
}

double QuickSort::getTempoGasto()
{
	return tempoGasto;
}

//Nao usei o std::swap para poder adicionar o de numero de trocas
void QuickSort::troca(tweets* &t1, tweets* &t2)
{
	if (t1 != t2) //Nao troca se t1 e t2 sao iguais, ja que nao precisa
	{
		//uso isso so pra testar, nao precisa. vou tirar quando tiver tudo pronto 100%
		//cout << "trocando " << t1->getTweetID() << " por " << t2->getTweetID() << endl;
		tweets* aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}

//Algoritmo de particionamento do vetor
int QuickSort::particiona(tweets* vet[], int inicio, int fim)
{
	//Seleciona o primeiro elemento do vetor como pivo (caso precise mudar o pivo, tem que mudar aqui e ali em baixo)
	int pivo = vet[inicio]->getTweetID();
	//Pega o elemento imediatamente a direita do pivo, para caminhar da esquerda para direita. Caso precise mudar o pivo, tem que mudar esse calculo tbm
	int esq = inicio + 1;
	//Pega o ultimo elemento do vetor para caminhar da direita para esquerda
	int dir = fim;

	//Caminhando no vetor enquanto os ponteiros nao se cruzam
	while (esq != dir)
	{
		if (vet[esq]->getTweetID() <= pivo)
		{
			esq++;//Caminha da esquerda para a direita
			numCompar++;
		}
		else
		{
			while ((esq != dir) && (pivo < vet[dir]->getTweetID()))
				{
					numCompar++;
					dir--; //Caminha da direita para a esquerda
				}
			troca(vet[esq], vet[dir]); //Faz a troca
		}
	}

	if (vet[esq]->getTweetID() > pivo)
	{
		esq--; //Volta
		numCompar++;
	}

	troca(vet[inicio], vet[esq]); //Se mudar o pivo, nao esquecer de mudar o pivo (vet[inicio]) nessa troca tambem
	return (esq); //Retorna a posiçao ordenada
}

//Algoritmo do quicksort recursivo
void QuickSort::quicksort(tweets* vet[], int ini, int fim)
{
	clock_t relogio;
	relogio = clock();
	if (ini < fim) 
	{
		int part = particiona(vet, ini, fim);
		quicksort(vet, ini, part-1);
		quicksort(vet, part+1, fim);
	}
	tempoGasto = (clock() - relogio) / (double)CLOCKS_PER_SEC;
}
