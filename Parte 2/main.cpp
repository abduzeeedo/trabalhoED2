/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

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

//Separa a string original em varias palavras, que sao armazenadas em um vetor
//ENTRADA: Uma string (tweet) e um vetor de palavras
//SAIDA(void): O vetor de palavras com cada palavra em uma posicao
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
                Palavra p(buffer, 1);
                vPal.push_back(p);
                buffer.clear();
            }
        }
    }
    //Adiciona a ultima palavra ao vetor
    Palavra p2(buffer, 1);
    vPal.push_back(p2);
    buffer.clear();
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

//Funcao randomiza o conteudo de um vetor de tweets
//ENTRADA: Ponteiro para vetor do tipo Tweet e tamanho do vetor
//SAIDA: O vetor de tweets com valores entre as posicoes randomizados (desordenado)
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
    int i; //Variavel para controle de iterações
    cout << "Digite o numero N de tweets a serem importados: ";
    int tam; //Quantidade de Tweets que serao lidos do arquivo txt
    cin >> tam;
    while (tam <= 0)
    {
        cout << "Tamanho invalido, digite um tamanho maior que 0: ";
        cin >> tam;
    }

    //Importando tweets do arquivo TXT
    GerTexto* ger = new GerTexto();
    int tamVet = tam * 2; //Serao instanciados 2 vezes o numero de tweets informados, para poder randomizar
    cout << "Instanciando " << tam << " tweets para realizar os testes, aguarde." << endl;
    Tweet** vTweet = ger->carregaTweets("test_set_tweets.txt", tamVet);

    //Randomizando o vetor de entrada para fazer o calculo da frequencia de N tweets aleatorios
    randomiza(vTweet, tamVet);

    //Le o numero N de tweets que o usuario deseja fazer a frequencia de palavras
    int n;
    cout << endl << "Digite o numero de tweets aleatorios para calcular a frequencia das palavras: ";
    cin >> n;
    while (n > tam || n <= 0)
    {
        cout << "Numero invalido, digite um numero entre 1 e " << tam << ": ";
        cin >> n;
    }

    //Preparando os tweets para ser calculada a frequencia
    cout << endl << "Preparando os tweets para ser calculada a frequencia, serao realizados [5] passos..." << endl;
    cout << "[1] Retirando todos os caracteres especiais, sinais de pontuacao e colocando todos os caracteres em minusculo." << endl;
    for (i = 0; i < tam; i++)
        vTweet[i]->setTweetText(limpaString(vTweet[i]->getTweetText()));

    //Separando todos os tweets em palavras diferentes
    cout << "[2] Separando todas as palavras dos tweets." << endl;
    vector<Palavra> vPalavras; //Cria um vetor de palavras para armazenar todas as palavras do tweet
    for (i = 0; i < n; i++)
        separaPalavras(vTweet[i]->getTweetText(), vPalavras);//Separa as palavras de cada tweet

    //Calculando o hashing de cada palavra
    cout << "[3] Calculando o hashing de cada palavra e calculando as frequencias." << endl;
    HashPalavra* hp;
    hp = new HashPalavra(vPalavras.size()/2);
    for (i = 0; i<vPalavras.size(); i++)
        hp->inserir(&vPalavras[i]);

    //Preparando o vetor para ordenacao
    cout << "[4] Preparando o vetor para a ordenacao." << endl;
    vector<Palavra> novo = hp->retornaVetor();  //Novo vetor com as palavras do hash
    vPalavras.clear();
    vPalavras = novo;

    //Ordenando o vetor por ordem de frequencia
    cout << "[5] Ordenando o vetor por ordem de frequencia usando MergeSort."<<endl;
    MergeSort ms;
    ms.mergesort(vPalavras, 0, vPalavras.size()-1);
    /*cout << "Exibindo palavras" << endl;
    hp->exibirTabela();*/
    cout << "-> Vetor ordenado, foram realizadas " << ms.getNumTrocas() << " trocas e " << ms.getNumComparacoes() << " comparacoes." << endl << endl;

    //Le o numero N de palavras que o usuario deseja ver a frequencia
    cout << "Digite o numero de palavras a serem exibidas com suas frequencias: ";
    int n_pal;
    cin.clear();
    cin >> n_pal;
    while (n_pal > vPalavras.size() || n_pal <= 0)
    {
        cout << "Numero invalido, digite um numero entre 1 e " << vPalavras.size() << ": ";
        cin >> n_pal;
    }

    //Imprimindo as n_pal palavras mais usadas
    cout << endl << "As [" << n_pal << "] palavras mais usadas sao:" << endl;
    for (i = 0; i<n_pal; i++)
    {
        cout << vPalavras[i].getFreq() << " - " << vPalavras[i].getConteudo() << endl;
    }

    system("pause");
    return 0;
}