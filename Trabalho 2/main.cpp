#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "Tweet.h"
#include "GerTexto.h"

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
	}
}

int main()
{
	imprimeMenu(); // Funcao para imprimir o Menu no Console

	/*Essa funcao sera usada para importar os tweets, cada posicao do vetor contem um numero
	que indica o numero de tweets aleatorios que devem ser importados e instanciados
	e depois, coloca-los em uma arvore*/
	vector<int> vEntrada = importaEntrada("entradaInsercao.txt");

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
	return 0;
}