#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "Tweet.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "Hashing.h"

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

//Metodo que seleciona a funcao a ser executada e finaliza execucao
void codigoFuncao() {
	string code;
	while (true) {
		cout << "Insira o Codigo de Função: (-1 para Encerrar Execução)" << endl;
		cin >> code;
		if (code == "-1") {
			return;
		}
		if (code == "0") {
			imprimeMenu();
		}
	}
}

int main()
{

	//imprimeMenu(); // Funcao para imprimir o Menu no Console

	// Instanciando 7 Tweet para teste
	Tweet* vetor[7];
	int tam = sizeof(vetor) / sizeof(vetor[0]);
	int id1 = 11;
	int tid1 = 121;
	string t = "teste de tweet1";
	string d = "2017-08-30 16:31:42";
	vetor[0] = new Tweet(id1, tid1, t.c_str(), d.c_str());
	vetor[1] = new Tweet(50, 14, t.c_str(), d.c_str());
	vetor[2] = new Tweet(98, 41, t.c_str(), d.c_str());
	vetor[3] = new Tweet(47, 98, t.c_str(), d.c_str());
	vetor[4] = new Tweet(26, 16, t.c_str(), d.c_str());
	vetor[5] = new Tweet(64, 189, t.c_str(), d.c_str());
	vetor[6] = new Tweet(54, 28, t.c_str(), d.c_str());

	// Começo das funçoes apenas para testes de ordenacao
	cout << "Antes de ordenar:" << endl;

	for (int k = 0; k < tam; k++)
	{
		cout << "[" << vetor[k]->getTweetID() << "]";
	}

	/* Deixar somente uma ordenaçao sem estar comentada, se não todas as outras irão pegar o vetor já ordenado pela primeira para ordenar */

	/*QuickSort*/
	//QuickSort ordena; //Chama a classes
	//ordena.quicksort(vetor, 0, tam-1, 'r'); //Faz o quicksort. Passar sempre 0 como inicio e tamanho-1 como final

	/*InsertionSort*/
	//InsertionSort ordena; //Chama a classe
	//ordena.insertionsort(vetor, 0, tam); //Faz o insertionsort. Passar 0 para ordenar desde o inicio e o tamanho total, nao tamanho-1

	/*MergeSort*/
	MergeSort ordena; //Chama a classe 
	ordena.mergesort(vetor, 0, tam-1); //Faz o mergesort. Passar sempre 0 como inicio e tamanho-1 como final
	
	/*BubbleSort*/
	//BubbleSort ordena; //Chama a classe
	//ordena.bubblesort(vetor, tam); //Faz o bubblesort. Passar o tamanho total, nao tamanho-1

	cout << endl << "Depois de ordenar:" << endl;
	for (int p = 0; p < tam; p++)
	{
		cout << "[" << vetor[p]->getTweetID() << "]";
	}

	cout << endl << endl;
	cout << "Numero de trocas: " << ordena.getNumTrocas() << endl;
	cout << "Numero de comparacoes: " << ordena.getNumComparacoes() << endl;
	cout << "Tempo gasto: " << ordena.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos, tenho que testar com mais.
	// Fim das funçoes apenas para testes de ordenacao

	codigoFuncao(); //Seleciona a funcao ou encerra a execução;
	//system("pause"); //coloquei isso pq se nao fica sumindo a janela no visual studio, pode tirar
	return 0;
}
