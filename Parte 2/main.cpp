#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <vector>
#include "Palavra.h"

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
	if(str[++j] == ' ')
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
				espaco = true; //Quando o caractere encontrado e uma letra, coloca a flag como true
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

void separaPalavras(string original, vector<Palavra> &vPal)
{
    string buffer;
    for (short i = 0; i<original.length(); i++) //Percorre a string orignal ate o seu final
    {
        if(original[i] != ' ') //Caso o caracter atual nao seja um espaco, adiciona ele no buffer
        {
            buffer += original[i];
        }
        else //Caso seja um espaco, transfere todo o buffer anterior (uma palavra completa) para o vetor de palavras
        {
            //Palavra* p = new Palavra(buffer,0);
            Palavra p(buffer,0);//Nao tenho certeza se e melhor fazer por ponteiro, se for eh so mudar
            vPal.push_back(p);
            buffer.clear();
        }
    }
    //Adiciona a ultima palavra ao vetor (sem isso, somente com o for, ele nao adiciona a ultima palavra)
    Palavra p2(buffer,0);
    vPal.push_back(p2);
    buffer.clear();
}

int main()
{
	//Hashing padrao do C
	hash<string> string_hash;

	//Palavras para testes
	string t1 = "palavra";
	string t2 = "Palavra";
	string t3 = "PALAVRA";
	string t4 = "arvalap";

	//Coloca todas as strings como minusculas (case insensitive)
	//O hashing padrao do C gera resultados diferentes dependendo se esta em caps lock ou nao
	//Por isso precisa de colocar tudo em minusculo para garantir
	transform(t1.begin(), t1.end(), t1.begin(), ::tolower);
	transform(t2.begin(), t2.end(), t2.begin(), ::tolower);
	transform(t3.begin(), t3.end(), t3.begin(), ::tolower);

	//Faz o hashing de todas as palavras
	unsigned int h1 = string_hash(t1);
	unsigned int h2 = string_hash(t2);
	unsigned int h3 = string_hash(t3);
	unsigned int h4 = string_hash(t4);
	cout << "-Resultados do hashing-" << endl;
	cout << t1 << " " << h1 << endl;
	cout << t2 << " " << h2 << endl;
	cout << t3 << " " << h3 << endl;
	cout << t4 << " " << h4 << endl;

	cout << endl << "==========================================================" << endl << endl;

	cout << "-Strings de testes de tweets-" << endl;
	string s1 = "este e um teste de tweet";
	cout << s1 << endl;
	string s2 = "Este, tambem, e um teste de tweet.";
	cout << s2 << endl;
	string s3 = "Mais um teste!!";
	cout << s3 << endl;
	string s4 = "Este tweet tem caracteres especiais: ! @ # $ % & * ( ) e mais alguns";
	cout << s4 << endl;
	string s5 = "teste de link http://www.google.com.br";
	cout << s5;
	cout << endl;

	//Coloca todas as strings como minusculas (case insensitive)
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	transform(s3.begin(), s3.end(), s3.begin(), ::tolower);
	transform(s4.begin(), s4.end(), s4.begin(), ::tolower);
	transform(s5.begin(), s5.end(), s5.begin(), ::tolower);

	cout << endl << "-Strings em minusculo sem os caracteres especiais e pontuacoes-" << endl;
	//Troca todos os sinais de pontuacao e caracteres especiais por espacos
	/*Nao usei o erase/remove porque em tweets que nao existe espacos entre a pontuacao, as palavras ficariam todas juntas dificultando dividir o tweet em varias palavras
	Exemplo: usando erase/remove no tweet Exemplo.de.tweet, iria ficar Exemplodetweet e isso ia contar como uma palavra so
	Usando o replace_if com espacos, ficaria Exemplo de tweet, o que eh o certo*/
	replace_if(s1.begin(), s1.end(), ::ispunct, ' ');
	cout << s1 << endl;
	replace_if(s2.begin(), s2.end(), ::ispunct, ' ');
	cout << s2 << endl;
	replace_if(s3.begin(), s3.end(), ::ispunct, ' ');
	cout << s3 << endl;
	replace_if(s4.begin(), s4.end(), ::ispunct, ' ');
	cout << s4 << endl;
	replace_if(s5.begin(), s5.end(), ::ispunct, ' ');
	cout << s5 << endl;

	cout << endl << "-Strings sem espacos desnecessarios-";
	//Tira todos os espacos desnecessarios das strings
	removeEspaco(s1);
	removeEspaco(s2);
	removeEspaco(s3);
	removeEspaco(s4);
	removeEspaco(s5);
	cout << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;

	/*Ao final de todos estes processos, todos os tweets estarao prontos para serem divididos em varias palavras para fazer o hashing delas
	todos os tweets estarao sem espacos desnecessarios, sem sinais de pontuacao e todas as letras minusculas (pois o hashing tem que ser case insensitive)*/

	//Separando os tweets em palavras diferentes
	vector<Palavra>vPalavra;
	separaPalavras(s4, vPalavra); //Testei apenas com uma string por vez mas fucniona para todas
	//Imprimindo o vetor de palavras para ver se ficou tudo certo
	cout<<endl<<"-Vetor de palavras separadas da string-"<<endl;
	for (short p = 0;p<vPalavra.size();p++)
    {
        cout<<vPalavra[p].getConteudo()<<endl;
    }

	//system("pause");
	return 0;
}
