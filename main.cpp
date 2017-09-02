#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"
#include "tweets.h"
#include "QuickSort.h"

using namespace std;

int main()
{
	// Instanciando 7 tweets para teste
	tweets* vetor[7];
	int id1 = 11;
	int tid1 = 121;
	string t = "teste de tweet1";
	string d = "2017-08-30 16:31:42";
	vetor[0] = new tweets(id1, tid1, t, d);
	vetor[1] = new tweets(50, 14, t, d);
	vetor[2] = new tweets(98, 41, t, d);
	vetor[3] = new tweets(47, 98, t, d);
	vetor[4] = new tweets(26, 16, t, d);
	vetor[5] = new tweets(64, 189, t, d);
	vetor[6] = new tweets(54, 28, t, d);

	/* Começo das funçoes apenas para testes do quicksort */
	cout << "antes de ordenar" << endl;
	for (int k = 0; k < 7; k++)
	{
		cout << vetor[k]->getTweetID() << endl;
	}
		
	QuickSort qs; //Chama a classe
	qs.quicksort(vetor, 0, 6); //Faz o quicksort. Passar sempre 0 como inicio e tamanho-1 como final
	int trocas = qs.getNumTrocas();
	int comp = qs.getNumComparacoes();

	cout << "depois de ordenar" << endl;
	for (int p = 0; p < 7; p++)
	{
		cout << vetor[p]->getTweetID() << endl;
	}

	cout << "numero de trocas: " << trocas << endl;
	cout << "numero de comparacoes: " << comp << endl;
	/* Fim das funçoes apenas para testes do quicksort */

	//system("pause"); //coloquei isso pq se nao fica sumindo a janela no visual studio, pode tirar
	return 0;
}
