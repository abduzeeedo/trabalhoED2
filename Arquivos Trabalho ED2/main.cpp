/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO: 
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

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
#include "HeapSort.h"
#include "GerTexto.h"
#include "HashStruct.h"
#include "HashEncad.h"

string salvar = "";
string saidasMenu = "";
using namespace std;


//Funcao usada para pegar as linhas do arquivo do Menu. 
//Entrada: Arquivo .txt com os dados do Menu 
//Saída: String lida na linha analizada.
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

//Funcao Que salva uma string em um arquivo .txt
//Entrada: String a ser salva e arquivo .txt onde os dados serao salvos. 
//Saida: Escrita da string passada por parametro em um arquivo .txt (tambem passado por parametro)
void salvarTxt(string salvar, string file) {
	ofstream arquivo;
	arquivo.open(file);
	arquivo << salvar << endl;
	//arquivo.close();
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
//Entrada: Arquivo .txt do menu a ser impresso em tela 
//Saida: Impressao em tela do Menu de opcoes
void imprimeMenu()
{
	ifstream leitor("menu.txt"); //Le o menu to txt
	string art = analisaLinhas(leitor);
	cout << art << endl; //Imprime o menu

	leitor.close();
}

//Funcao usada para imprimir todos os TweetID`s 
//Entrada: Vetor de objetos do tipo Tweet e tamanho de tal vetor. 
//Saida: Impressao em tela de todos os TweetID`s deste vetor
void imprimeTIDVetor(Tweet* vet[], int tam) {
	cout << "Vetor: ";
	for (int k = 0; k < tam; k++)
	{
		cout << "[" << vet[k]->getTweetID() << "]";
	}
	cout << endl;
}

//Funcao passada um ponteiro pra vetor do tipo Tweet, retorna um ponteiro pra um vetor com os mesmos valores com tamanho tam
//Entrada: Ponteiro para vetor do tipo Tweet, tamanho do vetor origem e destino
//Saida: Retorna um ponteiro para um vetor com "tam" objetos
Tweet** carregaTweets(Tweet** src, int tam, int tamVet) {
	Tweet** dst = new Tweet*[tam];
	for (int i = 0; i < tam; i++) {
		dst[i] = src[i];
	}
	return dst;
}

//Funcao randomiza o conteudo de um vetor de tweets
//Entrada: Ponteiro para vetor do tipo Tweet, tamanho do vetor origem seed do random
//Saida: O vetor de tweets com valores entre as posicoes randomizados (desordena)
void randomiza(Tweet** vetor, int tam, int seed) {
	srand(seed);
	for (int i = 0; i < tam; i++) {
		swap(vetor[rand() % tam], vetor[rand() % tam]);
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
		saidasMenu += "Algoritmo QuickSort Recursivo:\n";

	if (tipo == 'm')
		saidasMenu += "Algoritmo QuickSort Recursivo com Mediana entre 3 Valores:\n";

	if (tipo == 'M')
		saidasMenu += "Algoritmo QuickSort Recursivo com Mediana entre 5 Valores:\n";

	if (tipo == 'i')
		saidasMenu += "Algoritmo QuickSort Recursivo com Insercao com m=10.:\n";

	if (tipo == 'I')
		saidasMenu += "Algoritmo QuickSort Recursivo com Insercao com m=100:\n";

	saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
	saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
	saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";
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

//Funcao para testes em Lote de QuickSort
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via quicksort
void batchQS(Tweet** original, int tamVet) {
	vector<int> vEntrada = importaEntrada("entrada.txt");
	//int vEntrada[3] = { 10000, 30000, 60000 };
	QuickSort qs;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(QuickSort)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de QuickSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando Original por QuickSort Recursivo..." << endl;
			qs.quicksort(original, 0, vEntrada[i] - 1, 'r');

			salvar += "Algoritmo QuickSort Recursivo:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			qs.limpaDados();
			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando Original por QuickSort de Mediana m=3..." << endl;
			qs.quicksort(original, 0, vEntrada[i] - 1, 'm');

			salvar += "Algoritmo QuickSort Recursivo com Mediana entre 3 Valores:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			qs.limpaDados();
			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando Original por QuickSort de Mediana m=5..." << endl;
			qs.quicksort(original, 0, vEntrada[i] - 1, 'M');

			salvar += "Algoritmo QuickSort Recursivo com Mediana entre 5 Valores:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			qs.limpaDados();
			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando Original por QuickSort de Insercao m=10..." << endl;
			qs.quicksort(original, 0, vEntrada[i] - 1, 'i');

			salvar += "Algoritmo QuickSort Recursivo com Insercao com m=10:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			qs.limpaDados();
			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando Original por QuickSort com Insercao com m=100..." << endl;
			qs.quicksort(original, 0, vEntrada[i] - 1, 'I');

			salvar += "Algoritmo QuickSort Recursivo com Insercao com m=100:\n";
			salvar += "Numero de trocas: " + toString(qs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qs.getTempoGasto()) + "\n\n";

			qs.limpaDados();

		}
	}
}

//Funcao para testes em Lote de InsertionSort
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via InsertionSort
void batchIS(Tweet** original, int tamVet)
{
	//int vEntrada[3] = { 10000, 30000, 60000 };
	vector<int> vEntrada = importaEntrada("entrada.txt");
	InsertionSort is;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(InsertionSort)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de InsertionSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando o Vetor com Insertion Sort..." << endl;
			is.insertionsort(original, 0, vEntrada[i]);

			salvar += "Algoritmo InsertionSort:\n";
			salvar += "Numero de trocas: " + toString(is.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(is.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(is.getTempoGasto()) + "\n\n";
			is.limpaDados();
		}
	}
}

//Funcao para testes em Lote de MergeSort
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via MergeSort
void batchMS(Tweet** original, int tamVet)
{
	//int vEntrada[3] = { 10000, 30000, 60000 };
	vector<int> vEntrada = importaEntrada("entrada.txt");
	MergeSort ms;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(MergeSort)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de MergeSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando o Vetor com MergeSort Sort..." << endl;
			ms.mergesort(original, 0, vEntrada[i] - 1);

			salvar += "Algoritmo MergeSort:\n";
			salvar += "Numero de trocas: " + toString(ms.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(ms.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(ms.getTempoGasto()) + "\n\n";

			ms.limpaDados();
		}
	}
}

//Funcao para testes em Lote de BubbleSort
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via BubbleSort
void batchBS(Tweet** original, int tamVet)
{
	//int vEntrada[3] = { 10000, 30000, 60000 };
	vector<int> vEntrada = importaEntrada("entrada.txt");
	BubbleSort bs;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size() - 2; i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(BubbleSort)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de BubbleSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando o Vetor com BubbleSort..." << endl;
			bs.bubblesort(original, vEntrada[i]);

			salvar += "Algoritmo BubbleSort:\n";
			salvar += "Numero de trocas: " + toString(bs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(bs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(bs.getTempoGasto()) + "\n\n";

			bs.limpaDados();
		}
	}
}

//Funcao para testes em Lote de HeapSort
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via HeapSort
void batchHS(Tweet** original, int tamVet)
{
	//int vEntrada[3] = { 10000, 30000, 60000 };
	vector<int> vEntrada = importaEntrada("entrada.txt");
	HeapSort hs;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(HeapSort)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de HeapSort para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando o Vetor com HeapSort..." << endl;
			hs.heapsort(original, vEntrada[i]);

			salvar += "Algoritmo HeapSort:\n";
			salvar += "Numero de trocas: " + toString(hs.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(hs.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(hs.getTempoGasto()) + "\n\n";

			hs.limpaDados();

		}
	}
}

//Funcao para testes em Lote de QuickSort de Inteiros
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados de ordenacao via quicksort de inteiros
void batchQSi(Tweet** original, int tamVet) {
	//int vEntrada[3] = { 10000, 30000, 60000 };
	vector<int> vEntrada = importaEntrada("entrada.txt");
	QuickSortInt qsi;
	for (int k = 1; k <= 5; k++) {
		randomiza(original, tamVet, k);
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			cout << "Ordenando vetor de tamanho " << vEntrada[i] << " na iteracao " << k << "(QuickSort Inteiros)..." << endl;
			salvar += "\n================================================================================\n";
			salvar += "Iteracao Numero " + toString(k);
			salvar += "\n--------------------------------------------------------------------------------\n";
			salvar += "Batch de QuickSort Inteiros para N=" + toString(vEntrada[i]) + ": ";
			salvar += "\n================================================================================\n";

			cout << "Randomizando..." << endl;
			randomiza(original, vEntrada[i], i + k);

			cout << "Ordenando o Vetor com QuickSort Inteiros..." << endl;
			qsi.criaVet(original, vEntrada[i]);

			salvar += "Algoritmo QuickSort Inteiros:\n";
			salvar += "Numero de trocas: " + toString(qsi.getNumTrocas()) + "\n";
			salvar += "Numero de comparacoes: " + toString(qsi.getNumComparacoes()) + "\n";
			salvar += "Tempo gasto: " + toString(qsi.getTempoGasto()) + "\n\n";

			qsi.limpaDados();
		}
	}
}

//Funcao para testes em Lote das Funcoes de Hashing
//ENTRADA: Vetor de tweets obtido via arquivo txt e seu tamanho
//Arquivo txt com todas os resultados dos testes em Lote das Funcoes de Hashing
void batchHash(Tweet* vet[], int tam)
{
	vector<int> vEntrada = importaEntrada("entrada.txt");

	for (int k = 1; k <= 5; k++) {
		for (unsigned int i = 0; i < vEntrada.size(); i++) {
			tam = vEntrada[i];
			//Criando um vetor de inteiros para ser usado no hashing
			long long int* vetInt = (long long int*)malloc(sizeof(long long int) * tam);
			for (int i = 0; i < tam; i++)
			{
				vetInt[i] = vet[i]->getTweetID();
			}

			cout << "Tratando Colisao 1 com Vetor de Tamanho" << vEntrada[i] << " na iteracao " << k << "..." << endl;
			//TRATAMENTO DE COLISAO 1
			HashEncad *h1 = new HashEncad(tam, 1);
			for (int a = 0; a < tam; a++)
			{
				h1->inserir(vetInt[a]);
			}
			h1->salvarArquivo("saida2.txt");
			delete h1;

			cout << "Tratando Colisao 2 com Vetor de Tamanho" << vEntrada[i] << " na iteracao " << k << "..." << endl;
			//TRATAMENTO DE COLISAO 2
			HashEncad *h2 = new HashEncad(tam, 2);
			for (int b = 0; b < tam; b++)
			{
				h2->inserir(vetInt[b]);
			}
			h2->salvarArquivo("saida2.txt");
			delete h2;

			/*cout << "Tratando Colisao 3 com Vetor de Tamanho" << vEntrada[i] << " na iteracao " << k << "..." << endl;
			//TRATAMENTO DE COLISAO 3 - NAO ESTA FUNCIONANDO
			HashEncad *h3 = new HashEncad(tam, 3);
			for (int c = 0; c < tam; c++)
			{
			h3->inserir(vetInt[c]);
			}
			h3->salvarArquivo("saida2.txt");
			delete h3;*/


			cout << "Tratando Colisao 4 com Vetor de Tamanho" << vEntrada[i] << " na iteracao " << k << "..." << endl;
			//TRATAMENTO DE COLISAO 4
			HashEncad *h4 = new HashEncad(tam, 4);
			for (int d = 0; d < tam; d++)
			{
				h4->inserir(vetInt[d]);
			}
			h4->salvarArquivo("saida2.txt");
			delete h4;

			cout << "Tratando Colisao 5 e 6 com Vetor de Tamanho" << vEntrada[i] << " na iteracao " << k << "..." << endl;
			//TRATAMENTO DE COLISAO 5 e 6
			HashStruct *h5 = new HashStruct(tam);
			for (int e = 0; e < tam; e++)
			{
				h5->inserir(vetInt[e]);
			}
			h5->salvarArquivo("saida2.txt");
			delete h5;

			cout << "Randomizando..." << endl;
			randomiza(vet, tam, i + k);

			delete vetInt;
		}
	}
}

//Funcao para realizar testes em Batch de todos os Algoritmos
//ENTRADA: Vetor de tweets a serem testados e seu tamanho
//Arquivo txt com todas os resultados de ordenacao
void testesBatch(Tweet** vetor, int tamVet)
{
	batchQS(vetor, tamVet);
	cout << "Batch para Quicksort concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchQSi(vetor, tamVet);
	cout << "Batch para Quicksort de Inteiros concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchIS(vetor, tamVet);
	cout << "Batch para InsertionSort concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchMS(vetor, tamVet);
	cout << "Batch para MergeSort concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchBS(vetor, tamVet);
	cout << "Batch para BubbleSort concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchHS(vetor, tamVet);
	cout << "Batch para HeapSort concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;

	batchHash(vetor, tamVet);
	cout << "Batch para Hashing concluido. Verifique o arquivo saida.txt para ver os resultados." << endl;
}

//Metodo que seleciona via codigo de comando a funcao a ser executada e finaliza execucao
//ENTRADA: Vetor de objetos do tipo Tweet e o tamanho deste vetor
//SAIDA: Chamada de funcoes de acordo com o codigo inserido pelo usuario
void codigoFuncao(Tweet* vet[], int tam) {
	string code;
	while (true) {
		cout << endl << "Insira o Codigo de Funcao: (-1 para Encerrar Execucao, 0 Para imprimir Menu)" << endl;
		cin >> code;
		if (code == "-1") {
			return; //Finaliza a Execucao
		}

		if (code == "0") {
			imprimeMenu();//Imprime o Menu (via arquivo txt)
		}

		if (code == "1") { //Realiza QuickSort Recursivo Padrao, utilizando posicao média do vetor como pivo
			randomiza(vet, tam, stoi(code));
			tiposQuickSort(vet, tam, 'r'); //Tipo 'r': QuickSort Recursivo Padrao
			cout << "Ordenou via QuickSort Recursivo, verifique o arquivo saida.txt para ver os resultados." << endl;
		}

		if (code == "2") { //Realiza QuickSort Recursivo com Mediana entre 3 Valores
			randomiza(vet, tam, stoi(code));
			tiposQuickSort(vet, tam, 'm'); //Tipo 'm': QuickSort Recursivo com Mediana entre 3 valores
			cout << "Ordenou via QuickSort Recursivo com Mediana entre 3 Valores, verifique o arquivo saida.txt para ver os resultados." << endl;
		}

		if (code == "3") { //Realiza QuickSort Recursivo com Mediana entre 5 Valores
			randomiza(vet, tam, stoi(code));
			tiposQuickSort(vet, tam, 'M');//Tipo 'M': QuickSort Recursivo com Mediana entre 5 valores
			cout << "Ordenou via QuickSort Recursivo com Mediana entre 5 Valores, verifique o arquivo saida.txt para ver os resultados." << endl;
		}

		if (code == "4") { //Realiza QuickSort Recursivo com Insercao com m=10
			randomiza(vet, tam, stoi(code));
			tiposQuickSort(vet, tam, 'i');//Tipo 'M': QuickSort Recursivo com Inser��o com m=10
			cout << "Ordenou via QuickSort Recursivo com Insercao com m=10, verifique o arquivo saida.txt para ver os resultados." << endl;
		}

		if (code == "5") { //Realiza QuickSort Recursivo com Insercao com m=100
			randomiza(vet, tam, stoi(code));
			tiposQuickSort(vet, tam, 'I');//Tipo 'M': QuickSort Recursivo com Inser��o com m=100
			cout << "Ordenou via QuickSort Recursivo com Insercao com m=100, verifique o arquivo saida.txt para ver os resultados." << endl;
		}

		if (code == "6") { //Realiza InsertionSort
						   /*InsertionSort*/
			randomiza(vet, tam, stoi(code));
			InsertionSort ordena; //Chama a classe
			ordena.insertionsort(vet, 0, tam); //Faz o insertionsort. Passar 0 para ordenar desde o inicio e o tamanho total, nao tamanho-1

											   //Salvando resultados em TXT
			saidasMenu += "Algoritmo InsertionSort:\n";
			saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via InsertionSort, verifique o arquivo saida.txt para ver os resultados." << endl;

		}

		if (code == "7") { //Realiza MergeSort
						   /*MergeSort*/
			randomiza(vet, tam, stoi(code));
			MergeSort ordena; //Chama a classe 
			ordena.mergesort(vet, 0, tam - 1); //Faz o mergesort. Passar sempre 0 como inicio e tamanho-1 como final

											   //Salvando resultados em TXT
			saidasMenu += "Algoritmo MergeSort:\n";
			saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via MergeSort, verifique o arquivo saida.txt para ver os resultados." << endl;
		}
		if (code == "8") {
			/*HeapSort*/
			randomiza(vet, tam, stoi(code));
			HeapSort ordena; //Chama a classe 
			ordena.heapsort(vet, tam - 1); //Faz o mergesort. Passar sempre 0 como inicio e tamanho-1 como final

										   //Salvando resultados em TXT
			saidasMenu += "Algoritmo HeapSort:\n";
			saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via HeapSort, verifique o arquivo saida.txt para ver os resultados." << endl;
		}
		if (code == "9") { //Realiza BubbleSort
						   /*BubbleSort*/
			randomiza(vet, tam, stoi(code));
			BubbleSort ordena; //Chama a classe
			ordena.bubblesort(vet, tam); //Faz o bubblesort. Passar o tamanho total, nao tamanho-1

										 //Salvando resultados em TXT
			saidasMenu += "Algoritmo BubbleSort:\n";
			saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via BubbleSort, verifique o arquivo saida.txt para ver os resultados." << endl;
		}
		if (code == "10") { //Realiza QuickSort em um vetor de inteiros (TweetID's)
							/*Quicksort com vetor de inteiros*/
			QuickSortInt ordena;
			randomiza(vet, tam, stoi(code));
			cout << "Criando e Ordenando vetor de inteiros com TweetID" << endl;
			ordena.criaVet(vet, tam); //Essa funcao ja cria, ordena, imprime e desaloca o vetor de int com os tweetIDs

									  //Salvando resultados em TXT
			saidasMenu += "Algoritmo QuickSort com um Vetor de Inteiros:\n";
			saidasMenu += "Numero de trocas: " + toString(ordena.getNumTrocas()) + "\n";
			saidasMenu += "Numero de comparacoes: " + toString(ordena.getNumComparacoes()) + "\n";
			saidasMenu += "Tempo gasto: " + toString(ordena.getTempoGasto()) + "\n\n";

			cout << "Ordenou via QuickSort em vetor de Inteiros, verifique o arquivo saida.txt para ver os resultados." << endl;
		}
		if (code == "11") {
			batchQS(vet, tam);
		}
		if (code == "12") {
			batchQSi(vet, tam);
		}
		if (code == "13") {
			batchIS(vet, tam);
		}
		if (code == "14") {
			batchBS(vet, tam);
		}
		if (code == "15") {
			batchMS(vet, tam);
		}
		if (code == "16") {
			batchHS(vet, tam);
		}
		if (code == "17") {
			batchHash(vet, tam);
		}
		if (code == "18") {
			testesBatch(vet, tam);
		}
	}
}

int main()
{
	imprimeMenu(); // Funcao para imprimir o Menu no Console

	/*Essa funcao sera usada para importar os tweets, cada posicao do vetor contem um numero
	que indica o numero de tweets aleatorios que devem ser importados e instanciados
	e depois, fazer a ordenacao deles*/
	vector<int> vEntrada = importaEntrada("entrada.txt");

	//Importando tweets do arquivo TXT-------------------------------------------
	int tamVet = 3000000; //Quantidade de Tweets que serao lidos do arquivo txt
	GerTexto* ger = new GerTexto();
	cout << "Instanciando " << tamVet << " tweets para realizar os testes, aguarde." << endl;
	Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);
	//---------------------------------------------------------------------------

	/*//Atribui Tweets Aleatoriamente, para ser usado no Menu-----------------------
	int tam = 1000; //Tamanho do Vetor criado com Tweets Aleatorios
	cout << "Gerando um vetor com " << tam << " tweets aleatorios." << endl;
	Tweet** vAleatorio = carregaTweets(vTweet, tam, tamVet);
	//---------------------------------------------------------------------------*/

	//Faz os testes em sequencia com o vetor de tweet-----------------------------
	//cout << "Fazendo testes em lote:" << endl;
	//testesBatch(vTweet, tamVet);
	//---------------------------------------------------------------------------


	codigoFuncao(vTweet, tamVet);//Seleciona a funcao ou encerra a execucao;
	salvarTxt(salvar, "saida.txt");
	salvarTxt(saidasMenu, "saidasMenu.txt");
	return 0;
}