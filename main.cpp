#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "tweets.h"
#include "QuickSort.h"

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

void code() {
	char code = -1;
	while (code == -1) {
		cout << "Insira algo para encerrar" << endl;
		cin >> code;
	}
}

int main()
{

	imprimeMenu();
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

	cout << "depois de ordenar" << endl;
	for (int p = 0; p < 7; p++)
	{
		cout << vetor[p]->getTweetID() << endl;
	}

	cout << "numero de trocas: " << qs.getNumTrocas() << endl;
	cout << "numero de comparacoes: " << qs.getNumComparacoes() << endl;
	cout << "tempo gasto: " << qs.getTempoGasto() << endl; //Acho que o tempo sempre mostra 0 pois a ordenaçao está muito rapida com poucos elementos, tenho que testar com mais.
														   /* Fim das funçoes apenas para testes do quicksort */
	code();
	//system("pause"); //coloquei isso pq se nao fica sumindo a janela no visual studio, pode tirar
	return 0;
}