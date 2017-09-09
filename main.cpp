#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "Tweet.h"
#include "QuickSort.h"
#include "QuickSortInt.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "BubbleSort.h"
#include "GerTexto.h"
#include "HashStruct.h"
#include "HashEncad.h"

string salvar = "";
using namespace std;


//Funcao usada para pegar as linhas do arquivo do Menu. 
//Entrada: Arquivo .txt com os dados do Menu -- Saída: String lida na linha analizada.
string analisaLinhas(ifstream& File)
{
	string linhaVerif;

	if (File)
	{
		while (File.good())
		{
			string linhaTemp;
			getline(File, linhaTemp);
			linhaTemp += "\n";

			linhaVerif += linhaTemp;
		}
		return linhaVerif;
	}
	else
	{
		cout << "ERRO AO LER O ARQUIVO DE MENU" << endl;
		return 0;
	}
}

//fun��o para converter um int para String, usada na escrita de dados em arquivo txt
//Entrada: Numero Inteiro -- Saida: Representacao deste numero inteiro em uma String
string toString(double i)
{
	stringstream ss;
	ss << i;
	string retorno = ss.str();
	return retorno;
}

//Funcao de Impressao de Menu
//Entrada: Arquivo .txt do menu a ser impresso em tela  -- Saida: Impressao em tela do Menu de opcoes
void imprimeMenu()
{
	ifstream leitor("menu.txt"); //Le o menu to txt
	string art = analisaLinhas(leitor);
	cout << art << endl; //Imprime o menu

	leitor.close();
}

//Funcao usada para imprimir todos os TweetID`s 
//Entrada: Vetor de objetos do tipo Tweet e tamanho de tal vetor. -- Saida: Impressao em tela de todos os TweetID`s deste vetor
void imprimeTIDVetor(Tweet* vet[], int tam) {
	cout << "Vetor: ";
	for (int k = 0; k < tam; k++)
	{
		cout << "[" << vet[k]->getTweetID() << "]";
	}
	cout << endl;
}

//Funcao Que salva uma string em um arquivo .txt
//Entrada: String a ser salva e arquivo .txt onde os dados serao salvos. -- Saida: Escrita da string passada por parametro em um arquivo .txt (tambem passado por parametro)
void salvarTxt(string salvar, string file) {
	ofstream arquivo;
	arquivo.open(file);
	arquivo << salvar << endl;
	//arquivo.close();
}

Tweet** setRand(Tweet** src, int tam, int tamVet, int seed) {
	srand(seed);
	Tweet** dst = new Tweet*[tam];
	for (int i = 0; i < tam; i++) {
		int random = rand() % tamVet;
		while (src[random]->getUso() == true) {
			//random = rand() % tamVet;
			random = (random + 1) % tamVet;
		}
		Tweet* tw = new Tweet(src[random]->getUserID(), src[random]->getTweetID(), src[random]->getTweetText(), src[random]->getDate());
		src[random]->setUso(true);
		dst[i] = tw;
	}
	return dst;
}

//Marca todos os tweets como nao usados
void limpaUso(Tweet** vetor, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		if (vetor[i]->getUso() == true)
			vetor[i]->setUso(false);
	}
}

//Chama o QuickSort passando o tipo por Parametro
//ENTRADA: Vetor de Objetos do tipo Tweet, tamanho de tal vetor e codigo "Tipo", referente ao tipo de quicksort a ser realizado
//Tipo r: QuickSort Recursivo com Pivo Central
//Tipo m: QuickSort Recursivo com Pivo sendo a Mediana entre 3 valores aleatorios do vetor
//Tipo M: QuickSort Recursivo com Pivo sendo a Mediana entre 5 valores aleatorios do vetor
//Tipo i: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 10
//Tipo I: QuickSort Recursivo utilizando InsertionSort para particoes de tamanho menor ou igual a 100
//SAIDA: Realiza a Ordenaçao do vetor passado por parametro utilizando o tipo de quicksort tambem passado por parametro
//Por fim, salva os dados da ordenacao em um arquivo .txt para fins de comparacao
void tiposQuickSort(Tweet* vet[], int tam, char tipo) {

	QuickSort ordena; //Chama a classes
	ordena.quicksort(vet, 0, tam - 1, tipo); //Faz o quicksort. Passar sempre 0 como inicio e tamanho-1 como final.

	//"Armazena" os dados de saida pós ordenacao na String "saida", para ser posteriormente escrita em um arquivo .txt
	if (tipo == 'r')
		salvar += "Algoritmo QuickSort Recursivo:\n";
		cout << "Algoritmo QuickSort Recursivo." << endl;

	if (tipo == 'm')
		salvar += "Algoritmo QuickSort Recursivo com Mediana entre 3 Valores:\n";
		cout << "Algoritmo QuickSort Recursivo com Mediana entre 3 Valores:\n" << endl;

	if (tipo == 'M')
		salvar += "Algoritmo QuickSort Recursivo com Mediana entre 5 Valores:\n";
		cout << "Algoritmo QuickSort Recursivo com Mediana entre 5 Valores." << endl;

	if (tipo == 'i')
		salvar += "Algoritmo QuickSort Recursivo com Insercao com m=10.:\n";
		cout << "Algoritmo QuickSort Recursivo com Insercao com m=10." << endl;

	if (tipo == 'I')
		salvar += "Algoritmo QuickSort Recursivo com Insercao com m=100:\n";
		cout << "Algoritmo QuickSort Recursivo com Insercao com m=100" << endl;

	salvar += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
	salvar += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
	salvar += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

}

//Metodo que seleciona via codigo de comando a funcao a ser executada e finaliza execucao
//ENTRADA: Vetor de objetos do tipo Tweet e o tamanho deste vetor
//SAIDA: Chamada de funcoes de acordo com o codigo inserido pelo usuario
void codigoFuncao(Tweet* vet[], int tam) {
	string code;
	while (true) {
		cout << endl << "Insira o Codigo de Funcao: (-1 para Encerrar Execucao)" << endl;
		cin >> code;
		if (code == "-1") {
			return; //Finaliza a Execucao
		}

		if (code == "0") {
			imprimeMenu();//Imprime o Menu (via arquivo txt)
		}

		if (code == "1") { //Realiza QuickSort Recursivo Padrao, utilizando posicao média do vetor como pivo
			tiposQuickSort(vet, tam, 'r'); //Tipo 'r': QuickSort Recursivo Padrao
			cout << "Ordenou via QuickSort Recursivo." << endl;
		}

		if (code == "2") { //Realiza QuickSort Recursivo com Mediana entre 3 Valores
			tiposQuickSort(vet, tam, 'm'); //Tipo 'm': QuickSort Recursivo com Mediana entre 3 valores
			cout << "Ordenou via QuickSort Recursivo com Mediana entre 3 Valores." << endl;
		}

		if (code == "3") { //Realiza QuickSort Recursivo com Mediana entre 5 Valores
			tiposQuickSort(vet, tam, 'M');//Tipo 'M': QuickSort Recursivo com Mediana entre 5 valores
			cout << "Ordenou via QuickSort Recursivo com Mediana entre 5 Valores." << endl;
		}

		if (code == "4") { //Realiza QuickSort Recursivo com Insercao com m=10
			tiposQuickSort(vet, tam, 'i');//Tipo 'M': QuickSort Recursivo com Inser��o com m=10
			cout << "Ordenou via QuickSort Recursivo com Insercao com m=10." << endl;
		}

		if (code == "5") { //Realiza QuickSort Recursivo com Insercao com m=100
			tiposQuickSort(vet, tam, 'I');//Tipo 'M': QuickSort Recursivo com Inser��o com m=100
			cout << "Ordenou via QuickSort Recursivo com Insercao com m=100" << endl;
		}

		if (code == "6") { //Realiza InsertionSort
			/*InsertionSort*/
			InsertionSort ordena; //Chama a classe
			ordena.insertionsort(vet, 0, tam); //Faz o insertionsort. Passar 0 para ordenar desde o inicio e o tamanho total, nao tamanho-1

			//Salvando resultados em TXT
			salvar += "Algoritmo InsertionSort:\n";
			salvar += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via InsertionSort." << endl;

		}

		if (code == "7") { //Realiza MergeSort
			/*MergeSort*/
			MergeSort ordena; //Chama a classe 
			ordena.mergesort(vet, 0, tam - 1); //Faz o mergesort. Passar sempre 0 como inicio e tamanho-1 como final

			//Salvando resultados em TXT
			salvar += "Algoritmo MergeSort:\n";
			salvar += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";
	
			cout << "Ordenou via MergeSort:" << endl;
		}
		if (code == "8") {
			/*HeapSort*/
			cout << "Falta Implementar" << endl;
		}
		if (code == "9") { //Realiza BubbleSort
			/*BubbleSort*/

			BubbleSort ordena; //Chama a classe
			ordena.bubblesort(vet, tam); //Faz o bubblesort. Passar o tamanho total, nao tamanho-1

			//Salvando resultados em TXT
			salvar += "Algoritmo BubbleSort:\n";
			salvar += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via BubbleSort:" << endl;
		}
		if (code == "10") { //Realiza QuickSort em um vetor de inteiros (TweetID's)
			/*Quicksort com vetor de inteiros*/
			QuickSortInt ordena;

			cout << "Criando e ordenando vetor de inteiros com TweetID, isso pode demorar" << endl;
			ordena.criaVet(vet, tam); //Essa funcao ja cria, ordena, imprime e desaloca o vetor de int com os tweetIDs

			//Salvando resultados em TXT
			salvar += "Algoritmo QuickSort com um Vetor de Inteiros:\n";
			salvar += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via QuickSort em vetor de Inteiros:" << endl;
		}
	}

}

//Funcao para ler os N numeros aleatorios do arquivo entrada.txt
//ENTRADA: Arquivo .txt com dados de N numero aleatorios a serem inseridos
//SAIDA: Vetor do tipo Vector onde cada posicao contem um nemero contido em uma linha do arquivo passado por parametro
vector<int> importaEntrada(const char* nomeArquivo)
{
	int i = 0; //Variavel para controlar a posicao do vetor
	string linha; //Variavel para armazenar a linha no getline
	ifstream arquivo(nomeArquivo); //Abre o arquivo
	int N; //Tamanho do vetor
	if (arquivo.is_open()) //Verifica se o arquivo esta aberto
	{
		getline(arquivo, linha); //Le a primeira linha do arquivo
		N = stoi(linha); //Converte string para int
		vector<int> vEntrada(N); //Cria o vetor com N posicoes lidas da primeira linha
		while (!arquivo.eof()) //Continua lendo o arquivo
		{
			getline(arquivo, linha);
			vEntrada[i] = stoi(linha); //Armazena na posicao i do vetor o numero lido da linha
			i++;
		}
		arquivo.close(); //Fecha o arquivo
		return vEntrada; //Retorna o vetor
	}
	else //Caso o arquivo nao esteja aberto, mostra um erro.
		cout << "Erro ao abrir arquivo " << nomeArquivo << endl;
}


void batchQS(Tweet** vetor, int tamVet) {
	//vector<int> vEntrada = importaEntrada("entrada.txt");
	limpaUso(vetor, tamVet);
	int vEntrada[3] = { 100, 200, 300 };
	Tweet** original;
	QuickSort qs;
	for (int k=1; k <= 5; k++){
		limpaUso(vetor, tamVet);
		for (int i = 0; i < 3; i++) {

			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de QuickSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";
			
			cout << "Instanciando Original..." << endl;
			original = setRand(vetor, vEntrada[i], tamVet, i + k);
			cout << "Ordenando Original por QuickSort Recursivo..." << endl;
			qs.quicksort(original, 0, vEntrada[i]-1, 'r');
	
			salvar += "Algoritmo QuickSort Recursivo:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";
			free(original);
			qs.limpaDados();
			limpaUso(vetor, tamVet);
	
			cout << "Instanciando Original..." << endl;
			original = setRand(vetor, vEntrada[i], tamVet, i + k);
			cout << "Ordenando Original por QuickSort de Mediana m=3..." << endl;
			qs.quicksort(original, 0, vEntrada[i]-1, 'm');
	
			salvar += "Algoritmo QuickSort Recursivo com Mediana entre 3 Valores:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";
	
			free(original);
			qs.limpaDados();
			limpaUso(vetor, tamVet);
	
			cout << "Instanciando Original..." << endl;
			original = setRand(vetor, vEntrada[i], tamVet, i + k);
			cout << "Ordenando Original por QuickSort de Mediana m=3..." << endl;
			qs.quicksort(original, 0, vEntrada[i]-1, 'M');
	
			salvar += "Algoritmo QuickSort Recursivo com Mediana entre 5 Valores:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";
	
			free(original);
			qs.limpaDados();
			limpaUso(vetor, tamVet);
	
			cout << "Instanciando Original..." << endl;
			original = setRand(vetor, vEntrada[i], tamVet, i + k);
			cout << "Ordenando Original por QuickSort de Insercao m=10..." << endl;
			qs.quicksort(original, 0, vEntrada[i]-1, 'i');
	
			salvar += "Algoritmo QuickSort Recursivo com Insercao com m=10:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";
				
			free(original);
			qs.limpaDados();
			limpaUso(vetor, tamVet);

			cout << "Instanciando Original..." << endl;
			original = setRand(vetor, vEntrada[i], tamVet, i + k);
			cout << "Ordenando Original por QuickSort com Insercao com m=1000..." << endl;
			qs.quicksort(original, 0, vEntrada[i]-1, 'I');
	
			salvar += "Algoritmo QuickSort Recursivo com Insercao com m=100:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			free(original);
			qs.limpaDados();
			limpaUso(vetor, tamVet);
		}
	}
}

void batchIS(Tweet** vetor, int tamVet)
{
	int vEntrada[3] = { 50, 100, 150 };
	Tweet** original;
	InsertionSort is;
	limpaUso(vetor, tamVet);
	for (int k = 1; k <= 5; k++) {
		for (int i = 0; i < 3; i++) {
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de InsertionSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";
			original = setRand(vetor, vEntrada[i], tamVet, i + k);

			is.insertionsort(original, 0, vEntrada[i]);

			salvar += "Algoritmo InsertionSort:\n";
			salvar += "Numero de trocas: " + toString(is.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(is.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(is.getTempoGasto()) + "\n\n";
			free(original);
			is.limpaDados();
			limpaUso(vetor, tamVet);
		}
	}
}

void batchMS(Tweet** vetor, int tamVet)
{
	int vEntrada[3] = { 50, 100, 150 };
	Tweet** original;
	MergeSort ms;
	limpaUso(vetor, tamVet);
	for (int k = 1; k <= 5; k++) {
		for (int i = 0; i < 3; i++) {
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de MergeSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";
			original = setRand(vetor, vEntrada[i], tamVet, i + k);

			ms.mergesort(original, 0, vEntrada[i] - 1);

			salvar += "Algoritmo MergeSort:\n";
			salvar += "Numero de trocas: " + toString(ms.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ms.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ms.getTempoGasto()) + "\n\n";
			free(original);
			ms.limpaDados();
			limpaUso(vetor, tamVet);
		}
	}
}

void batchBS(Tweet** vetor, int tamVet)
{
	int vEntrada[3] = { 50, 100, 150 };
	Tweet** original;
	BubbleSort bs;
	limpaUso(vetor, tamVet);
	for (int k = 1; k <= 5; k++) {
		for (int i = 0; i < 3; i++) {
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de BubbleSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";
			original = setRand(vetor, vEntrada[i], tamVet, i + k);

			bs.bubblesort(original, vEntrada[i]);

			salvar += "Algoritmo BubbleSort:\n";
			salvar += "Numero de trocas: " + toString(bs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(bs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(bs.getTempoGasto()) + "\n\n";
			free(original);
			bs.limpaDados();
			limpaUso(vetor, tamVet);
		}
	}
}

void testesBatch(Tweet** vetor, int tamVet)
{
	batchQS(vetor, tamVet);
	cout << "Batch para Quicksort concluido. Verifique o arquivo saida.txt para ver os resultados" << endl;

	batchIS(vetor, tamVet);
	cout << "Batch para InsertionSort concluido. Verifique o arquivo saida.txt para ver os resultados" << endl;

	batchMS(vetor, tamVet);
	cout << "Batch para MergeSort concluido. Verifique o arquivo saida.txt para ver os resultados" << endl;

	batchBS(vetor, tamVet);
	cout << "Batch para BubbleSort concluido. Verifique o arquivo saida.txt para ver os resultados" << endl;
}

int main()
{
	imprimeMenu(); // Funcao para imprimir o Menu no Console

	 /*Essa funcao sera usada para importar os tweets, cada posicao do vetor contem um numero
	 que indica o numero de tweets aleatorios que devem ser importados e instanciados
	 e depois, fazer a ordenacao deles
	 Para usar um for neste vetor, basta fazer for (int i = 0; i < vEntrada.size(); i++)*/
	vector<int> vEntrada = importaEntrada("entrada.txt");

	//Importa tweets do arquivo TXT
	//--------------------------------------------------------------------
	int tamVet = 10000; //Quantidade de Tweets que serao lidos do arquivo txt
	GerTexto* ger = new GerTexto();
	cout << "Instanciando " << tamVet << " tweets." << endl;
	Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);
	//---------------------------------------------------------------------

	//Atribui Tweets Aleatoriamente 
	//--------------------------------------------------------------------
	int tam = 5000; //Tamanho do Vetor criado com Tweets Aleatorios
	cout << "Gerando um vetor com " << tam << " tweets aleatorios." << endl;
	Tweet** vAleatorio = setRand(vTweet, tam, tamVet, 1);
	//--------------------------------------------------------------------

	//Faz os testes em sequencia com o tweet 
	//--------------------------------------------------------------------
	cout << "Fazendo testes em lote:" << endl;
	testesBatch(vTweet, tamVet);
	//--------------------------------------------------------------------

	codigoFuncao(vAleatorio, tam);//Seleciona a funcao ou encerra a execucao;
	salvarTxt(salvar, "saida.txt");
	return 0;
}
