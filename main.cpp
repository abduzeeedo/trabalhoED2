#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "tweets.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "BubbleSort.h"

using namespace std;

//Funcao usada para pegar as linhas do arquivo do Menu
std::string parseart(std::ifstream& File)
{
	std::string parsedfile;

	if (File)
	{
		while (File.good())
		{
			std::string tmpline;
			std::getline(File, tmpline);
			tmpline += "\n";

			parsedfile += tmpline;
		}
		return parsedfile;
	}
	else
	{
		cout << "ERRO AO LER O ARQUIVO DE MENU" << endl;
		return 0;
	}
}

//Funcao de Impressao de Menu
void imprimeMenu()
{
	std::ifstream leitor("menu.txt"); //Le o menu to txt
	std::string art = parseart(leitor);
	std::cout << art << std::endl; //Imprime o menu

	leitor.close();
}

void imprimeVetor(tweets* vet[], int tam) {
	cout << "Vetor: ";
	for (int k = 0; k < tam; k++)
	{
		cout << "[" << vet[k]->getTweetID() << "]";
	}
	cout << endl;
}

//Chama o quickSort passando o tipo por Parametro
void tiposQuickSort(tweets* vet[], int tam, char tipo) {

	/*QuickSort*/
	imprimeVetor(vet, tam);
	cout << endl;

	QuickSort ordena; //Chama a classes
	ordena.quicksort(vet, 0, tam - 1, tipo); //Faz o quicksort. Passar sempre 0 como inicio e tamanho-1 como final.

	cout << "Depois de Ordenar:" << endl;
	imprimeVetor(vet, tam);
	cout << endl;

	//Resultado das Operações
	cout << "Numero de trocas: " << ordena.getNumTrocas() << endl;
	cout << "Numero de comparacoes: " << ordena.getNumComparacoes() << endl;
	cout << "Tempo gasto: " << ordena.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos, tenho que testar com mais
}

//Metodo que seleciona a funcao a ser executada e finaliza execucao
void codigoFuncao(tweets* vet[], int tam) {
	string code;
	while (true) {
		cout << endl << "Insira o Codigo de Funcao: (-1 para Encerrar Execução)" << endl;
		cin >> code;
		if (code == "-1") {
			return;
		}

		if (code == "0") {
			imprimeMenu();
		}

		if (code == "1") {
			cout << "Antes de Ordenar via QuickSort Recursivo:" << endl;
			tiposQuickSort(vet, tam, 'r'); //Tipo 'r': QuickSort Recursivo Padrao
		}

		if (code == "2") {
			cout << "Falta Implementar" << endl;
			/*
			cout << "Antes de Ordenar via QuickSort Recursivo com Mediana entre 3 Valores:" << endl;
			tiposQuickSort(vet, tam, 'm'); //Tipo 'm': QuickSort Recursivo com Mediana entre 3 valores
			*/
		}

		if (code == "3") {
			cout << "Falta Implementar" << endl;
			/*
			cout << "Antes de Ordenar via QuickSort Recursivo com Mediana entre 5 Valores:" << endl;
			tiposQuickSort(vet, tam, 'M');//Tipo 'M': QuickSort Recursivo com Mediana entre 5 valores
			*/
		}

		if (code == "4") {
			cout << "Antes de Ordenar via QuickSort Recursivo com Inserção com m=10:" << endl;
			tiposQuickSort(vet, tam, 'i');//Tipo 'M': QuickSort Recursivo com Inserção com m=10
		}

		if (code == "5") {
			cout << "Antes de Ordenar via QuickSort Recursivo com Inserção com m=100:" << endl;
			tiposQuickSort(vet, tam, 'I');//Tipo 'M': QuickSort Recursivo com Inserção com m=100
		}

		if (code == "6") {
			/*InsertionSort*/
			cout << "Antes de Ordenar via InsertionSort:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			InsertionSort ordena; //Chama a classe
			ordena.insertionsort(vet, 0, tam); //Faz o insertionsort. Passar 0 para ordenar desde o inicio e o tamanho total, nao tamanho-1

			cout << "Depois de Ordenar:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			//Resultado das Operações
			cout << "Numero de trocas: " << ordena.getNumTrocas() << endl;
			cout << "Numero de comparacoes: " << ordena.getNumComparacoes() << endl;
			cout << "Tempo gasto: " << ordena.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos, tenho que testar com mais
		}

		if (code == "7") {
			/*MergeSort*/
			cout << "Antes de Ordenar via MergeSort:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			
			MergeSort ordena; //Chama a classe 
			ordena.mergesort(vet, 0, tam - 1); //Faz o mergesort. Passar sempre 0 como inicio e tamanho-1 como final

			cout << "Depois de Ordenar:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			//Resultado das Operações
			cout << "Numero de trocas: " << ordena.getNumTrocas() << endl;
			cout << "Numero de comparacoes: " << ordena.getNumComparacoes() << endl;
			cout << "Tempo gasto: " << ordena.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos
		}
		if (code == "8") {
			/*HeapSort*/
			cout << "Falta Implementar" << endl;
		}
		if (code == "9") {
			/*BubbleSort*/
			cout << "Antes de Ordenar via BubbleSort:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			BubbleSort ordena; //Chama a classe
			ordena.bubblesort(vet, tam); //Faz o bubblesort. Passar o tamanho total, nao tamanho-1

			cout << "Depois de Ordenar:" << endl;
			imprimeVetor(vet, tam);
			cout << endl;

			//Resultado das Operações
			cout << "Numero de trocas: " << ordena.getNumTrocas() << endl;
			cout << "Numero de comparacoes: " << ordena.getNumComparacoes() << endl;
			cout << "Tempo gasto: " << ordena.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos
		}
	}
}

int main()
{

	imprimeMenu(); // Funcao para imprimir o Menu no Console

	// Instanciando 7 tweets para teste
	tweets* vetor[7];
	int tam = sizeof(vetor) / sizeof(vetor[0]);
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

	codigoFuncao(vetor, tam); //Seleciona a funcao ou encerra a execução;
	//system("pause"); //coloquei isso pq se nao fica sumindo a janela no visual studio, pode tirar
	return 0;
}