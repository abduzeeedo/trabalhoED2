#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include "Palavra.h"
#include "Tweet.h"
#include "GerTexto.h"
#include "MergeSort.h"
#include "HashTweet.h"
#include "HashPalavra.h"
using namespace std;

/*
//Funcao de hashing que achei na net, caso nao possa usar o hashing padrao
//Alterar ela se for usar mesmo
unsigned int hasht(const char* s)
{
unsigned int h = 0;
for (; *s; ++s)
{
h += *s;
h += (h << 10);
h ^= (h >> 6);
}
h += (h << 3);
h ^= (h >> 11);
h += (h << 15);
return h;
}
*/

//Remove os espacos a mais de uma string, feito in-place e O(n) onde n eh o tamanho da palavra
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

//Separa a string original em varias palavras, que sao armazenadas em um vetor
void separaPalavras(string original, vector<Palavra> &vPal)
{
	string buffer;
	for (short i = 0; i<original.length(); i++) //Percorre a string orignal ate o seu final
	{
		if (original[i] != ' ') //Caso o caracter atual nao seja um espaco, adiciona ele no buffer
		{
			buffer += original[i];
		}
		else //Caso seja um espaco, transfere todo o buffer anterior (uma palavra completa) para o vetor de palavras
		{
			if (buffer.size() < 2)//Ignora palavras com menos de 2 letras
				buffer.clear();
			else
			{
				//Palavra* p = new Palavra(buffer,0);
				Palavra p(buffer, 1);//Nao tenho certeza se e melhor fazer por ponteiro, se for eh so mudar
				vPal.push_back(p);
				buffer.clear();
			}
		}
	}
	//Adiciona a ultima palavra ao vetor (sem isso, somente com o for, ele nao adiciona a ultima palavra)
	Palavra p2(buffer, 1);
	vPal.push_back(p2);
	buffer.clear();
}

//Verifica se a letra e valida (se e de A a Z ou um numero)
bool charInvalido(const char &c)
{
	if ((c <= 'Z' && c >= 'A') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return false;
	else
		return true;
}

//Remove todas as pontuacoes, espacos, caracteres especiais e coloca todas as letras em minusculo
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

//Funcao auxiliar para ordenar o vetor em ordem alfabetica
bool ordenacao(Palavra p1, Palavra p2)
{
	if (p1.getConteudo() > p2.getConteudo())
		return true;
	else
		return false;
}

//Verifica se uma palavra eh igual a outra
bool ehIgual(Palavra &p1, Palavra &p2)
{
	if (p1.getConteudo() == p2.getConteudo())
    {
        return true;
    }
	else
		return false;
}

//Funcao auxiliar para preparar o vetor para ser ordenado
void preparaVetor(vector<Palavra> &vPal)
{
	sort(vPal.begin(), vPal.end(), ordenacao);//Ordena o vetor em ordem alfabetica
	vPal.erase(unique(vPal.begin(), vPal.end(), ehIgual), vPal.end());//Elimina palavras repetidas (eh necessario ordenar em ordem alfabetica primeiro)
}

//Funcao randomiza o conteudo de um vetor de tweets
//Entrada: Ponteiro para vetor do tipo Tweet, tamanho do vetor origem seed do random
//Saida: O vetor de tweets com valores entre as posicoes randomizados (desordena)
void randomiza(Tweet** vetor, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		srand(2*i+tam); //Troca a seed do rand a cada iteraçao
		swap(vetor[rand() % tam], vetor[rand() % tam]);
	}
}

int main()
{
	cout << "Digite o numero N de tweets a serem importados: " << endl;
	int tam; //Quantidade de Tweets que serao lidos do arquivo txt
	cin >> tam;
	while (tam <= 0)
	{
		cout << "Tamanho invalido, digite um tamanho maior que 0" << endl;
		cin >> tam;
	}

	//Importando tweets do arquivo TXT
	GerTexto* ger = new GerTexto();
	int tamVet = tam * 2; //Serao instanciados 2 vezes o numero de tweets informados, para poder randomizar
	cout << "Instanciando " << tam << " tweets para realizar os testes, aguarde." << endl;
	Tweet** vTweet = ger->carregaTweets("tw.txt", tamVet);

	//Randomizando o vetor de entrada para fazer o calculo da frequencia de N tweets aleatorios
	randomiza(vTweet, tamVet);

	//Le o numero N de tweets que o usuario deseja fazer a frequencia de palavras
	int n;
	cout << endl << "Digite o numero de tweets aleatorios para calcular a frequencia das palavras: " << endl;
	cin >> n;
	while (n > tam || n <= 0)
	{
		cout << "Numero invalido, digite um numero entre 1 e " << tam << endl;
		cin >> n;
	}

	int i; //Variavel para controle de iterações
	//Preparando os tweets para ser calculada a frequencia
	cout << endl << "Preparando os tweets para ser calculada a frequencia, serao realizados [5] passos..." << endl;
	cout << "[1] Retirando todos os caracteres especiais, sinais de pontuacao, colocando todas as strings em minusculo e calculando as frequencias." << endl;
	for (i = 0; i < tam; i++)
		vTweet[i]->setTweetText(limpaString(vTweet[i]->getTweetText()));

	//Separando todos os tweets em palavras diferentes
	cout << "[2] Separando todas as palavras dos tweets." << endl;
	vector<Palavra> vPalavras; //Cria um vetor de palavras para armazenar todas as palavras do tweet
	for (i = 0; i < n; i++)
		separaPalavras(vTweet[i]->getTweetText(), vPalavras);//Separa as palavras de cada tweet

	//Desalocando o vetor de tweets original (nao ta desalocando n sei pq)
	delete[] vTweet;
	delete ger;
	vTweet = NULL;
	ger = NULL;

	/*----------------ALTERAR O HASHING AQUI----------------*/
	//Calculando o hashing de cada palavra
	cout << "[3] Calculando o hashing de cada palavra." << endl;
	/*hash<string> string_hash;//Hashing padrao do C

	*/
	HashPalavra* hp = new HashPalavra(vPalavras.size());
	for (i = 0; i<vPalavras.size(); i++)
	{
	    hp->inserir(&vPalavras[i]);
		//vPalavras[i].setHash(string_hash(vPalavras[i].getConteudo()));
	}

	//Preparando o vetor para ordenacao
	cout << "[4] Preparando o vetor para a ordenacao." << endl;
    vector<Palavra> vPalavras2 = hp->retornaVetor(); //novo vetor com as palavras do hash
	//Ordenando o vetor por ordem de frequencia
	cout << "[5] Ordenando o vetor por ordem de frequencia usando MergeSort." << endl;
	MergeSort ms;
	ms.mergesort(vPalavras2, 0, vPalavras2.size()-1);
	cout << "Exibindo palavras" << endl;
    hp->exibirTabela();
	cout << "Vetor ordenado, foram realizadas " << ms.getNumTrocas() << " trocas e " << ms.getNumComparacoes() << " comparacoes." << endl << endl;

	//Le o numero N de palavras que o usuario deseja ver a frequencia
	cout << "Digite o numero de palavras a serem exibidas com suas frequencias: " << endl;
	int n_pal;
	cin.clear();
	cin >> n_pal;
	while (n_pal > vPalavras2.size() || n_pal <= 0)
	{
		cout << "Numero invalido, digite um numero entre 1 e " << vPalavras2.size() << endl;
		cin >> n_pal;
	}

	//Imprimindo as n_pal palavras mais usadas
	cout << endl << "As [" << n_pal << "] palavras mais usadas sao:" << endl;
	for (i = 0; i<n_pal; i++)
	{
		cout << vPalavras2[i].getFreq() << " - " << vPalavras2[i].getConteudo() << endl;
	}

	//system("pause");
	return 0;
}
