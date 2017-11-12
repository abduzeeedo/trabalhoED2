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
#include <stdlib.h>
#include "Tweet.h"
#include "GerTexto.h"
#include "ArvoreSplay.h"
#include "arvoreB.h"
#include "AVL.h"
#include "ArvoreVP.h"

string saidasInsercao = "";
string saidasBusca = "";
string saidasRemocao = "";
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
void randomiza(Tweet** vetor, int tam, int seed) {
	srand(seed);
	for (int i = 0; i < tam; i++) {
		swap(vetor[rand() % tam], vetor[rand() % tam]);
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
			long int numeroComp = 0;
			long int numeroCopias = 0;
			double tempoGasto = 0;

			long int numeroCompBusca = 0;
			double tempoBusca = 0;

			long int numeroCompRemocao = 0;
			double tempoRemocao = 0;

			vector<int> vEntrada = importaEntrada("entradaInsercao.txt");

			for (unsigned int i = 0; i < vEntrada.size(); i++) {
				for (int k = 1; k <= 5; k++) {
					randomiza(vet, vEntrada[i], vEntrada[i]/k);
					ArvoreSplay* arvoreSplay = new ArvoreSplay();
					int ias;
					//Insere os tweets na arvore
					for (ias = 0; ias < vEntrada[i]; ias++)
					{
						arvoreSplay->insereNo(vet[ias]);
					}
	
					cout << "Arvore Splay criada na Interacao " << k << ", Entrada de Tamanho " << vEntrada[i] << "." << "\n";
					cout << "Tempo total gasto nas insercoes: " << arvoreSplay->gettempoInsercao() << endl;
					cout << "Numero de comparacoes feitas: " << arvoreSplay->getnumCompar() << endl;
					cout << "Numero de copias de registro feitas: " << arvoreSplay->getnumCopias() << "\n" << endl;

					////armazena dados em variaveis para tirar media posteriormente
					numeroComp += arvoreSplay->getnumCompar();
					numeroCopias += arvoreSplay->getnumCopias();
					tempoGasto += arvoreSplay->gettempoInsercao();
					arvoreSplay->limpaDados();

					//realiza uma busca aleatoria
					cout << "Realizando Busca..." << endl;
					arvoreSplay->busca(vet[rand()]);

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompBusca += arvoreSplay->getnumCompar();
					tempoBusca += arvoreSplay->gettempoBusca();
					arvoreSplay->limpaDados();

					//realiza uma remocao aleatoria
					cout << "Realizando Remocao..." << endl;
					arvoreSplay->removeNo(vet[rand()]);

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompRemocao += arvoreSplay->getnumCompar();
					tempoRemocao += arvoreSplay->gettempoRemocao();
					arvoreSplay->limpaDados();

					delete arvoreSplay;
				}
				saidasInsercao += "==========================================================\n";
				saidasInsercao += "Arvore Splay, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasInsercao += "Tempo total gasto nas insercoes: " + toString(tempoGasto/5) + "\n";
				saidasInsercao += "Numero de comparacoes feitas: " + toString(numeroComp/5) + "\n";
				saidasInsercao += "Numero de copias de registro feitas: " + toString(numeroCopias/5) + "\n\n";
				saidasInsercao += "==========================================================\n";

				saidasBusca += "==========================================================\n";
				saidasBusca += "Arvore Splay, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasBusca += "Tempo total gasto na Busca: " + toString(tempoBusca / 5) + "\n";
				saidasBusca += "Numero de comparacoes feitas: " + toString(numeroCompBusca / 5) + "\n";
				saidasBusca += "==========================================================\n";

				saidasRemocao += "==========================================================\n";
				saidasRemocao += "Arvore Splay, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasRemocao += "Tempo total gasto na Remocao: " + toString(tempoRemocao / 5) + "\n";
				saidasRemocao += "Numero de comparacoes feitas: " + toString(numeroCompRemocao / 5) + "\n";
				saidasRemocao += "==========================================================\n";
			}
		}
		if (code == "2")
		{
			long int numeroComp = 0;
			long int numeroCopias = 0;
			double tempoGasto = 0;

			long int numeroCompBusca = 0;
			double tempoBusca = 0;

			long int numeroCompRemocao = 0;
			double tempoRemocao = 0;

			vector<int> vEntrada = importaEntrada("entradaInsercao.txt");
			for (unsigned int i = 0; i < vEntrada.size(); i++) {
				for (int k = 1; k <= 5; k++) {
					randomiza(vet, vEntrada[i], vEntrada[i] / k);
					AVL* arvoreAVL = new AVL();
					arvoreAVL->limpaDados();
					int iav;
					//Insere os tweets na arvore
					for (iav = 0; iav < tam; iav++)
					{
						arvoreAVL->inserir(vet[iav]);
					}

					cout << "Arvore AVL criada na Interacao " << k << ", Entrada de Tamanho " << vEntrada[i] << "." << "\n";
					cout << "Tempo total gasto nas insercoes: " << arvoreAVL->getTempoInsercao() << endl;
					cout << "Numero de comparacoes feitas: " << arvoreAVL->getNumCompar() << endl;
					cout << "Numero de copias de registro feitas: " << arvoreAVL->getNumCopias() << "\n" << endl;

					//armazena dados em variaveis para tirar media posteriormente
					numeroComp += arvoreAVL->getNumCompar();
					numeroCopias += arvoreAVL->getNumCopias();
					tempoGasto += arvoreAVL->getTempoInsercao();
					arvoreAVL->limpaDados();

					//realiza uma busca aleatoria
					cout << "Realizando Busca..." << endl;
					arvoreAVL->busca(vet[rand()]->getTweetID());

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompBusca += arvoreAVL->getNumCompar();
					tempoBusca += arvoreAVL->getTempoBusca();
					arvoreAVL->limpaDados();

					//realiza uma remocao aleatoria
					cout << "Realizando Remocao..." << endl;
					arvoreAVL->remover(vet[rand()]);

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompRemocao += arvoreAVL->getNumCompar();
					tempoRemocao += arvoreAVL->getTempoRemocao();

					delete arvoreAVL;
				}
				saidasInsercao += "==========================================================\n";
				saidasInsercao += "Arvore AVL, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasInsercao += "Tempo total gasto nas insercoes: " + toString(tempoGasto/5) + "\n";
				saidasInsercao += "Numero de comparacoes feitas: " + toString(numeroComp/5) + "\n";
				saidasInsercao += "Numero de copias de registro feitas: " + toString(numeroCopias/5) + "\n\n";
				saidasInsercao += "==========================================================\n";

				saidasBusca += "==========================================================\n";
				saidasBusca += "Arvore AVL, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasBusca += "Tempo total gasto na Busca: " + toString(tempoBusca / 5) + "\n";
				saidasBusca += "Numero de comparacoes feitas: " + toString(numeroCompBusca / 5) + "\n";
				saidasBusca += "==========================================================\n";

				saidasRemocao += "==========================================================\n";
				saidasRemocao += "Arvore AVL, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasRemocao += "Tempo total gasto na Remocao: " + toString(tempoRemocao / 5) + "\n";
				saidasRemocao += "Numero de comparacoes feitas: " + toString(numeroCompRemocao / 5) + "\n";
				saidasRemocao += "==========================================================\n";
			}
		}
		if (code == "3")
		{
			long int numeroComp = 0;
			long int numeroCopias = 0;
			double tempoGasto = 0;

			long int numeroCompBusca = 0;
			double tempoBusca = 0;

			long int numeroCompRemocao = 0;
			double tempoRemocao = 0;

			vector<int> vEntrada = importaEntrada("entradaInsercao.txt");
			for (unsigned int i = 0; i < vEntrada.size(); i++) {
				for (int k = 1; k <= 5; k++) {
					randomiza(vet, vEntrada[i], vEntrada[i] / k);
					ArvoreB* arvoreB = new ArvoreB();
					arvoreB->limpaDados();
					int iab;
					//Insere os tweets na arvore
					for (iab = 0; iab < tam; iab++)
					{
						arvoreB->inserir(vet[iab]->getTweetID());
					}

					cout << "\n" << "Arvore B criada na Interacao " << k << ", Entrada de Tamanho " << vEntrada[i] << "." << "\n";
					cout << "Tempo total gasto nas insercoes: " << arvoreB->getTempoInsercao() << endl;
					cout << "Numero de comparacoes feitas: " << arvoreB->getNumCompar() << endl;
					cout << "Numero de copias de registro feitas: " << arvoreB->getNumCopias() << endl;


					numeroComp += arvoreB->getNumCompar();
					numeroCopias += arvoreB->getNumCopias();
					tempoGasto += arvoreB->getTempoInsercao();
					arvoreB->limpaDados();

					//realiza uma busca aleatoria
					cout << "Realizando Busca..." << endl;
					arvoreB->buscar(vet[rand()]->getTweetID());

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompBusca += arvoreB->getNumCompar();
					tempoBusca += arvoreB->getTempoBusca();
					arvoreB->limpaDados();

					//realiza uma remocao aleatoria
					cout << "Realizando Remocao..." << endl;
					arvoreB->remover(vet[rand()]->getTweetID());

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompRemocao += arvoreB->getNumCompar();
					tempoRemocao += arvoreB->getTempoRemocao();

					delete arvoreB;
				}
				saidasInsercao += "==========================================================\n";
				saidasInsercao += "Arvore B, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasInsercao += "Tempo total gasto nas insercoes: " + toString(tempoGasto / 5) + "\n";
				saidasInsercao += "Numero de comparacoes feitas: " + toString(numeroComp / 5) + "\n";
				saidasInsercao += "Numero de copias de registro feitas: " + toString(numeroCopias / 5) + "\n\n";
				saidasInsercao += "==========================================================\n";

				saidasBusca += "==========================================================\n";
				saidasBusca += "Arvore B, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasBusca += "Tempo total gasto na Busca: " + toString(tempoBusca / 5) + "\n";
				saidasBusca += "Numero de comparacoes feitas: " + toString(numeroCompBusca / 5) + "\n";
				saidasBusca += "==========================================================\n";

				saidasRemocao += "==========================================================\n";
				saidasRemocao += "Arvore B, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasRemocao += "Tempo total gasto na Remocao: " + toString(tempoRemocao / 5) + "\n";
				saidasRemocao += "Numero de comparacoes feitas: " + toString(numeroCompRemocao / 5) + "\n";
				saidasRemocao += "==========================================================\n";
			}
		}
		if (code == "4")
		{
			long int numeroComp = 0;
			long int numeroCopias = 0;
			double tempoGasto = 0;

			long int numeroCompBusca = 0;
			double tempoBusca = 0;

			long int numeroCompRemocao = 0;
			double tempoRemocao = 0;

			vector<int> vEntrada = importaEntrada("entradaInsercao.txt");
			for (unsigned int i = 0; i < vEntrada.size(); i++) {
				for (int k = 1; k <= 5; k++) {
					randomiza(vet, vEntrada[i], vEntrada[i] / k);
					ArvoreVP* arvoreVP = new ArvoreVP();
					int iavp;
					//Insere os tweets na arvore
					for (iavp = 0; iavp < tam; iavp++)
					{
						arvoreVP->insere(vet[iavp]->getTweetID());
					}

					cout << "\n" << "Arvore Vermelho/Preta criada na Interacao " << k << ", Entrada de Tamanho " << vEntrada[i] << "." << "\n";
					cout << "Tempo total gasto nas insercoes: " << arvoreVP->getTempoInsercao() << endl;
					cout << "Numero de comparacoes feitas: " << arvoreVP->getNumCompar() << endl;
					cout << "Numero de copias de registro feitas: " << arvoreVP->getNumCopias() << endl;

					numeroComp += arvoreVP->getNumCompar();
					numeroCopias += arvoreVP->getNumCopias();
					tempoGasto += arvoreVP->getTempoInsercao();
					arvoreVP->limpaDados();

					//realiza uma busca aleatoria
					cout << "Realizando Busca..." << endl;
					arvoreVP->buscar(vet[rand()]->getTweetID());

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompBusca += arvoreVP->getNumCompar();
					tempoBusca += arvoreVP->getTempoBusca();
					arvoreVP->limpaDados();

					//realiza uma remocao aleatoria
					cout << "Realizando Remocao..." << endl;
					arvoreVP->remover(vet[rand()]->getTweetID());

					//armazena dados em variaveis para tirar media posteriormente
					numeroCompRemocao += arvoreVP->getNumCompar();
					tempoRemocao += arvoreVP->getTempoRemocao();
					arvoreVP->limpaDados();

					delete arvoreVP;
				}
				saidasInsercao += "==========================================================\n";
				saidasInsercao += "Arvore Vermelho-Preta, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasInsercao += "Tempo total gasto nas insercoes: " + toString(tempoGasto / 5) + "\n";
				saidasInsercao += "Numero de comparacoes feitas: " + toString(numeroComp / 5) + "\n";
				saidasInsercao += "Numero de copias de registro feitas: " + toString(numeroCopias / 5) + "\n\n";
				saidasInsercao += "==========================================================\n";

				saidasBusca += "==========================================================\n";
				saidasBusca += "Arvore Vermelho-Preta, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasBusca += "Tempo total gasto na Busca: " + toString(tempoBusca / 5) + "\n";
				saidasBusca += "Numero de comparacoes feitas: " + toString(numeroCompBusca / 5) + "\n";
				saidasBusca += "==========================================================\n";

				saidasRemocao += "==========================================================\n";
				saidasRemocao += "Arvore Vermelho-Preta, Média entre 5 interacoes com entrada de Tamanho " + toString(vEntrada[i]) + "\n";
				saidasRemocao += "Tempo total gasto na Remocao: " + toString(tempoRemocao / 5) + "\n";
				saidasRemocao += "Numero de comparacoes feitas: " + toString(numeroCompRemocao / 5) + "\n";
				saidasRemocao += "==========================================================\n";
			}
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
	int tamVet = 2000000; //Quantidade de Tweets que serao lidos do arquivo txt
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

	salvarTxt(saidasInsercao, "saidasInsercao.txt");
	salvarTxt(saidasBusca, "saidasBusca.txt");
	salvarTxt(saidasRemocao, "saidasRemocao.txt");
	system("pause");
	return 0;
}