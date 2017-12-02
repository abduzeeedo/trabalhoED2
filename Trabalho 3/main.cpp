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
#include <algorithm>
#include "Tweet.h"
#include "GerTexto.h"
#include "Huffman.h"

string saida = "";
string saida_Huf = "";
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
	arquivo.close();
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
void randomiza(Tweet** vetor, int tam) {
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

//Remove os espacos a mais de uma string, feito in-place e O(n) onde n eh o tamanho da string (tweet)
//ENTRADA: uma string (tweet)
//SAIDA: a mesma string, sem espacos desnecessarios (apenas um espaco entre cada palavra)
void removeEspaco(string &str)
{
	//i = posicao vazia na "nova" string
	//j = posicao da proxima letra a ser inserida na string original
	//tam = tamanho da string (condicao de parada)
	//espaco = flag para nao retirar espacos necessarios (precisa ter pelo menos um espaco entre cada palavra)
	size_t tam = str.length();
	short i = 0;
	short j = -1;
	bool espaco = false;

	//Percorre por todos os espacos no comeco do texto, se houver algum
	if (str[++j] == ' ')
		while (++j < tam && str[j] == ' ');

	//Comeca a leitura da string
	while (j < tam)
	{
		if (str[j] != ' ')
		{
			str[i++] = str[j++]; //Coloca a letra da posicao j na posicao i e aumenta os indices
			espaco = false; //Quando o caractere encontrado e uma letra, coloca a flag como false
		}
		else if (str[j++] == ' ')
		{
			if (!espaco)
			{
				str[i++] = ' '; //Adiciona apenas um espaco (necessario) entre uma palavra e outra
				espaco = true; //Quando o caractere encontrado nao e uma letra, coloca a flag como true
			}
		}
	}
	//Remove todos os epacos no final do texto, se houver algum
	if (i <= 1)
		str.erase(str.begin() + i, str.end());
	else
	{
		if (str[i - 1] == ' ')
			str.erase(str.begin() + i - 1, str.end());
		else
			str.erase(str.begin() + i, str.end());
	}
}

//Verifica se a letra e valida (se e de A a Z ou um numero)
//ENTRADA: uma variavel do tipo const char
//SAIDA: verdadeiro/falso dependendo se a variavel eh uma letra/numero ou nao
bool charInvalido(const char &c)
{
	if ((c <= 'Z' && c >= 'A') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return false;
	else
		return true;
}

//Remove todas as pontuacoes, espacos, caracteres especiais e coloca todas as letras em minusculo
//ENTRADA: Uma string (tweet)
//SAIDA: Uma string contendo as mesmas palavras da entrada porem em letras minusculas e sem sinais de pontuacao.
string limpaString(string original)
{
	string s = original;
	/*Nao usei o erase/remove porque em tweets que nao existe espacos entre a pontuacao, as palavras ficariam todas juntas dificultando dividir o tweet em varias palavras
	Exemplo: usando erase/remove no tweet Exemplo.de.tweet, iria ficar Exemplodetweet e isso ia contar como uma palavra so
	Usando o replace_if com espacos, ficaria Exemplo de tweet, o que eh o certo*/
	transform(s.begin(), s.end(), s.begin(), ::tolower);//Coloca as letras em minusculo
	replace_if(s.begin(), s.end(), charInvalido, ' ');//Troca todos os sinais de pontuacao e caracteres especiais por espacos
	removeEspaco(s);//Remove os espacos desneessarios
	return s;
}

//Metodo que seleciona via codigo de comando a funcao a ser executada e finaliza execucao
//ENTRADA: Vetor de objetos do tipo Tweet e o tamanho deste vetor
//SAIDA: Chamada de funcoes de acordo com o codigo inserido pelo usuario
void codigoFuncao(Tweet* vet[], int tam) {
	string code;
	/*Essa funcao sera usada para importar os tweets, cada posicao do vetor contem um numero
	que indica o numero de tweets aleatorios que devem ser importados e instanciados
	para serem comprimidos*/
	vector<int> vEntrada = importaEntrada("entrada.txt");

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
			cout << "Fazendo a compressao de tweets usando metodo Huffman..." << endl;
			string comprime;

			for (int v = 0; v < vEntrada.size(); v++)
			{
				Huffman* huf = new Huffman();
				cout << endl;
				saida += "\n================================================================================\n";
				cout << "Iteracao " << v+1 << " de " << vEntrada.size() << "." << endl;
				saida += "Metodo Huffman - Iteracao " + toString(v+1) + " de " + toString(vEntrada.size()) + ".\n";
				cout << "Fazendo a compressao de " << vEntrada[v] << " tweets." << endl;
				saida += "Fazendo a compressao de " + toString(vEntrada[v]) + " tweets.\n";
				cout << "[1] Criando string com todos os tweets pedidos." << endl;
				/*Cria uma string com todos os tweets que foram passados*/
				for (int h = 0; h < vEntrada[v]; h++)
				{
					comprime += vet[h]->getTweetText();
					comprime += "\n"; //Pula uma linha a cada tweet
				}

				cout << "[2] Salvando string em arquivo de texto." << endl;
				/*Salva a string sem estar comprimida num TXT para comprar os tamanhos depois*/
				string salvaSemCompressao = "Huffman_SemCompressao_Iteracao_" + toString(v+1) + ".txt";
				salvarTxt(comprime, salvaSemCompressao);

				cout << "[3] Codificando a string." << endl;
				/*Comprime a string*/
				saida_Huf += huf->codifica(comprime);

				cout << "[4] Salvando string codificada em um novo arquivo de texto." << endl;
				/*Salva a string comprimida bit por bit em um novo TXT*/
				string salvaCompresso = "Huffman_Compresso_Iteracao_" + toString(v+1) + ".txt";
				huf->salvaBinario(salvaCompresso, saida_Huf);

				cout << "Compressao de tweets usando metodo Huffman completa." << endl;
				saida += "Compressao de tweets usando metodo Huffman completa.\n";
				cout << "Tamanho ocupado antes da compressao: " << comprime.size() << " bytes." << endl;
				saida += "Tamanho ocupado antes da compressao: " + toString(comprime.size()) + " bytes.\n";
				/*Divide por 8 pois como eh uma string, cada 1 e 0 tem 8 bits e nao 1.*/
				cout << "Tamanho ocupado apos a compressao: " << saida_Huf.size() / 8 << " bytes." << endl;
				saida += "Tamanho ocupado apos a compressao: " + toString(saida_Huf.size()/8) + " bytes.\n";
				cout << "Tempo gasto pela compressao: " << huf->getTempoGasto() << endl;
				saida += "Tempo gasto pela compressao: " + toString(huf->getTempoGasto());
				cout << endl;
				saida += "\n================================================================================\n";
				comprime.clear();
				saida_Huf.clear();
				delete huf;
			}
		}

		if (code == "2") {
			cout << "Fazendo a compressao de tweets usando metodo LZ77..." << endl;
		}

		if (code == "3") {
			cout << "Fazendo a compressao de tweets usando metodo LZ78..." << endl;
		}

		if (code == "4") {
			cout << "Fazendo a compressao de tweets usando metodo LZW..." << endl;
		}
	}
}

int main()
{
	int i; //Variavel para controle de iteracoes
	imprimeMenu(); // Funcao para imprimir o Menu no Console

	//Importando tweets do arquivo TXT-------------------------------------------
	int tamVet = 500; //Quantidade de Tweets que serao lidos do arquivo txt
	GerTexto* ger = new GerTexto();
	cout << "[1] Instanciando " << tamVet << " tweets para realizar os testes, aguarde." << endl;
	Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);
	//---------------------------------------------------------------------------

	//Randomizando o vetor de entrada para fazer o calculo da frequencia de N tweets aleatorios
	randomiza(vTweet, tamVet);

	/* Para facilitar em algumas compressoes, removemos todos os caracteres que nao sao letras ou numeros das strings
	e tambem colocamos todas as letras em minusculo */
	cout << "[2] Retirando todos os caracteres especiais, sinais de pontuacao e colocando todos os caracteres em minusculo." << endl;
	for (i = 0; i < tamVet; i++)
		vTweet[i]->setTweetText(limpaString(vTweet[i]->getTweetText()));

	codigoFuncao(vTweet, tamVet);//Seleciona a funcao ou encerra a execucao;
	salvarTxt(saida, "saidas.txt");
	system("pause");
	return 0;
}