﻿/*---------------------------------------
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
#include <stdlib.h>
#include "Tweet.h"
#include "GerTexto.h"
#include "ArvoreSplay.h"
#include "arvoreB.h"
#include "AVL.h"

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
//ENTRADA: Ponteiro para vetor do tipo Tweet e tamanho do vetor
//SAIDA: O vetor de tweets com valores entre as posicoes randomizados (desordenado)
void randomiza(Tweet** vetor, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		srand(2 * i + tam); //Troca a seed do rand a cada iteraçao
		swap(vetor[rand() % tam], vetor[rand()*(i + 2) % tam]);
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
		N = atoi(linha.c_str()); //Converte string para int
		vector<int> vEntrada(N); //Cria o vetor com N posicoes lidas da primeira linha
		while (!arquivo.eof()) //Continua lendo o arquivo
		{
			getline(arquivo, linha);
			vEntrada[i] = atoi(linha.c_str()); //Armazena na posicao i do vetor o numero lido da linha
			i++;
		}
		arquivo.close(); //Fecha o arquivo
		return vEntrada; //Retorna o vetor
	}
	else //Caso o arquivo nao esteja aberto, mostra um erro.
		cout << "Erro ao abrir arquivo " << nomeArquivo << endl;
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

		if (code == "1") {
			ArvoreSplay* as = new ArvoreSplay();
			int ias;
			//Insere os tweets na arvore
			for (ias = 0; ias < tam; ias++)
			{
				as->insereNo(vet[ias]);
			}
			/*
			Como fazer a remocao/busca na Arvore Splay:
			1- Ler o tweet ID
			2- Buscar no vetor mesmo vetor utilizado para insercao o ponteiro para o tweetID
			3- Chamar a remocao/busca na arvore com o ponteiro encontrado

			Exemplo: Remover o tweet de ID 10524432019 (eh o 10 tweet do arquivo test_set_tweets)
			for (ias = 0; ias < tam; ias++)
			{
				if (vet[ias]->getTweetID() == 10524432019) //Achou o tweet, sai do for
				{
					break;
				}
			}
			//Faz a busca/remocao na arvore com a posicao do vetor de tweet encontrado, caso ele exista
			if(vet[ias]->getTweetID() == 10524432019)
			{
				as->busca(vTweet[ias]);
				as->removeNo(vTweet[ias]);
			}
			else
			{
				cout << "Tweet nao encontrado!" << endl;
			}
			*/
			cout << "Arvore Splay criada." << endl;
			cout << "Tempo total gasto nas insercoes: " << as->gettempoInsercao() << endl;
			cout << "Numero de comparacoes feitas: " << as->getnumCompar() << endl;
			cout << "Numero de copias de registro feitas: " << as->getnumCopias() << endl;
			delete as;
		}
		if(code == "2")
        {
            AVL* arvoreAVL = new AVL();
            int iav;
			//Insere os tweets na arvore
			for (iav = 0; iav < tam; iav++)
			{
				arvoreAVL->inserir(vet[iav]);
			}
			cout << "Arvore AVL criada." << endl;
			cout << "Tempo total gasto nas insercoes: " << arvoreAVL->getTempoInsercao() << endl;
			cout << "Numero de comparacoes feitas: " << arvoreAVL->getNumCompar() << endl;
			cout << "Numero de copias de registro feitas: " << arvoreAVL->getNumCompias() << endl;
			delete arvoreAVL;
        }
		if (code == "3")
		{
			ArvoreB* arvoreB = new ArvoreB();
			int iab;
			//Insere os tweets na arvore
			for (iab = 0; iab < tam; iab++)
			{
				arvoreB->inserir(vet[iab]->getTweetID());
			}
			cout << "Arvore B criada." << endl;
			cout << "Tempo total gasto nas insercoes: " << arvoreB->getTempoInsercao() << endl;
			cout << "Numero de comparacoes feitas: " << arvoreB->getNumCompar() << endl;
			cout << "Numero de copias de registro feitas: " << arvoreB->getNumCompias() << endl;
			delete arvoreB;
		}
	}
}

int main()
{
	imprimeMenu(); // Funcao para imprimir o Menu no Console

	/*Essa funcao sera usada para importar os tweets, cada posicao do vetor contem um numero
	que indica o numero de tweets aleatorios que devem ser importados e instanciados
	e depois, coloca-los em uma arvore*/
	//vector<int> vEntrada = importaEntrada("entradaInsercao.txt");

	//Importando tweets do arquivo TXT-------------------------------------------
	int tamVet = 100; //Quantidade de Tweets que serao lidos do arquivo txt
	GerTexto* ger = new GerTexto();
	cout << "Instanciando " << tamVet << " tweets para realizar os testes, aguarde." << endl;
	Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);
	//---------------------------------------------------------------------------

	/*//Atribui Tweets Aleatoriamente, para ser usado no Menu-----------------------
	int tam = 1000; //Tamanho do Vetor criado com Tweets Aleatorios
	cout << "Gerando um vetor com " << tam << " tweets aleatorios." << endl;
	Tweet** vAleatorio = carregaTweets(vTweet, tam, tamVet);
	//---------------------------------------------------------------------------*/

	codigoFuncao(vTweet, tamVet);//Seleciona a funcao ou encerra a execucao;
	salvarTxt(salvar, "saida.txt");
	salvarTxt(saidasMenu, "saidasMenu.txt");
	system("pause");
	return 0;
}