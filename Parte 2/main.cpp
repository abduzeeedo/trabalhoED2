#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Palavra.h"
#include "Tweet.h"
#include "GerTexto.h"

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
				Palavra p(buffer, 0);//Nao tenho certeza se e melhor fazer por ponteiro, se for eh so mudar
				vPal.push_back(p);
				buffer.clear();
			}
		}
	}
	//Adiciona a ultima palavra ao vetor (sem isso, somente com o for, ele nao adiciona a ultima palavra)
	Palavra p2(buffer, 0);
	vPal.push_back(p2);
	buffer.clear();
}

//Remove todas as pontuacoes, espacos, caracteres especiais e coloca todas as letras em minusculo
string limpaString(string original)
{
    string s = original;
	/*Nao usei o erase/remove porque em tweets que nao existe espacos entre a pontuacao, as palavras ficariam todas juntas dificultando dividir o tweet em varias palavras
	Exemplo: usando erase/remove no tweet Exemplo.de.tweet, iria ficar Exemplodetweet e isso ia contar como uma palavra so
	Usando o replace_if com espacos, ficaria Exemplo de tweet, o que eh o certo*/
	replace_if(s.begin(), s.end(), ::ispunct, ' ');//Troca todos os sinais de pontuacao e caracteres especiais por espacos
	transform(s.begin(), s.end(), s.begin(), ::tolower);//Coloca as letras em minusculo
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
	if (p1.getHash() == p2.getHash())
    {
        p1.aumentaFreq();
        return true;
    }
	else
		return false;
}

//Funcao auxiliar para ordenacao do vetor em base das frequencias (sera substituido pelo MergeSort na implementacao final)
bool ordenaFreq(Palavra p1, Palavra p2)
{
	if (p1.getFreq() > p2.getFreq())
		return true;
	else
		return false;
}

//Funcao auxiliar para deixar o vetor de palavras ordenado por frequencia
void ordenaVetor(vector<Palavra> &vPal)
{
	sort(vPal.begin(), vPal.end(), ordenacao);//Ordena o vetor em ordem alfabetica
	vPal.erase(unique(vPal.begin(), vPal.end(), ehIgual), vPal.end());//Elimina palavras repetidas (eh necessario ordenar em ordem alfabetica primeiro)
	sort(vPal.begin(), vPal.end(), ordenaFreq);//Ordena o vetor por ordem de frequencia (sera substituido pelo MergeSort na implementacao final)
}

//Funcao randomiza o conteudo de um vetor de tweets
//Entrada: Ponteiro para vetor do tipo Tweet, tamanho do vetor origem seed do random
//Saida: O vetor de tweets com valores entre as posicoes randomizados (desordena)
void randomiza(Tweet** vetor, int tam, int seed)
{
	srand(seed);
	for (int i = 0; i < tam; i++)
		swap(vetor[rand() % tam], vetor[rand() % tam]);
}

int main()
{
	cout << "Digite o numero N de tweets a serem importados: " << endl;
	int tam; //Quantidade de Tweets que serao lidos do arquivo txt
	cin >> tam;

	//Importando tweets do arquivo TXT
	GerTexto* ger = new GerTexto();
	int tamVet = tam * 2; //Serao instanciados 2 vezes o numero de tweets informados, para poder randomizar
	cout << "Instanciando " << tam << " tweets para realizar os testes, aguarde." << endl;
	Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);

	//Randomizando o vetor de entrada para fazer o calculo da frequencia de N tweets aleatorios
	randomiza(vTweet, tamVet, 0);

	//Le o numero N de tweets que o usuario deseja fazer a frequencia de palavras
	short n;
	cout << "Digite o numero de tweets aleatorios para calcular a frequencia das palavras: " << endl;
	cin >> n;

	int i; //Variavel para controle de iterações
	//Preparando os tweets para ser calculada a frequencia
	cout << "Preparando os tweets para ser calculada a frequencia, serao realizados [4] passos..." << endl;
	cout << "[1] Retirando todos os caracteres especiais, sinais de pontuacao e colocando todas as strings em minusculo e calculando as frequencias." << endl;
	for (i = 0; i < tam; i++)
		vTweet[i]->setTweetText(limpaString(vTweet[i]->getTweetText()));

	//Separando todos os tweets em palavras diferentes
	cout << "[2] Separando todas as palavras dos tweets." << endl;
	vector<Palavra> vPalavras; //Cria um vetor de palavras para armazenar todas as palavras do tweet
	for (i = 0; i < n; i++)
		separaPalavras(vTweet[i]->getTweetText(),vPalavras);//Separa as palavras de cada tweet

	//Calculando o hashing de cada palavra
	cout << "[3] Calculando o hashing de cada palavra." << endl;
	hash<string> string_hash;//Hashing padrao do C
	for (i = 0; i<vPalavras.size(); i++)
	{
		vPalavras[i].setHash(string_hash(vPalavras[i].getConteudo()));
	}

	//Ordenando o vetor por ordem de frequencia
	cout << "[4] Ordenando o vetor por ordem de frequencia." << endl;
	ordenaVetor(vPalavras);

	//Le o numero N de palavras que o usuario deseja ver a frequencia
	cout << "Digite o numero de palavras a serem exibidas com suas frequencias: " << endl;
	int n_pal;
	cin.clear();
	cin >> n_pal;

	//Imprimindo as n_pal palavras mais usadas
	cout << endl << "Palavras mais usadas:" << endl;
	for (i = 0; i<n_pal; i++)
	{
		cout << vPalavras[i].getFreq() << " - " << vPalavras[i].getConteudo() << endl;
	}

	//system("pause");
	return 0;
}
