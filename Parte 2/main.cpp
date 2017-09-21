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
            if(buffer.size()>2)//Ignora palavras com 2 letras ou menos
            {
            //Palavra* p = new Palavra(buffer,0);
            Palavra p(buffer,0);//Nao tenho certeza se e melhor fazer por ponteiro, se for eh so mudar
            vPal.push_back(p);
            buffer.clear();
            }
        }
    }
    //Adiciona a ultima palavra ao vetor (sem isso, somente com o for, ele nao adiciona a ultima palavra)
    Palavra p2(buffer,0);
    vPal.push_back(p2);
    buffer.clear();
}
//Coloca todos os caracteres da string em minusculo
void sMinusculo(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}
//Remove todas as pontuacoes, espacos e caracteres especiais de uma string
void limpaString(string &s)
{
    /*Nao usei o erase/remove porque em tweets que nao existe espacos entre a pontuacao, as palavras ficariam todas juntas dificultando dividir o tweet em varias palavras
	Exemplo: usando erase/remove no tweet Exemplo.de.tweet, iria ficar Exemplodetweet e isso ia contar como uma palavra so
	Usando o replace_if com espacos, ficaria Exemplo de tweet, o que eh o certo*/
    replace_if(s.begin(), s.end(), ::ispunct, ' ');
    removeEspaco(s);
}

int main()
{
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
    //O hashing padrao do C gera resultados diferentes dependendo se esta em caps lock ou nao
	//Por isso precisa de colocar tudo em minusculo para garantir
	sMinusculo(s1);
	sMinusculo(s2);
	sMinusculo(s3);
	sMinusculo(s4);
	sMinusculo(s5);

	cout << endl << "-Strings em minusculo sem os caracteres especiais, espacos e pontuacoes-" << endl;
	//Troca todos os sinais de pontuacao e caracteres especiais por espacos e depois remove os espacos desnecessarios
	limpaString(s1);
	limpaString(s2);
	limpaString(s3);
	limpaString(s4);
	limpaString(s5);
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;

	/*Ao final de todos estes processos, todos os tweets estarao prontos para serem divididos em varias palavras para fazer o hashing delas
	todos os tweets estarao sem espacos desnecessarios, sem sinais de pontuacao e todas as letras minusculas (pois o hashing tem que ser case insensitive)*/

    cout << endl << "==========================================================" << endl << endl;

    //Fazendo o hashing de um tweet exemplo e calculando o uso de cada
    //Hashing padrao do C
	hash<string> string_hash;
	string teste = "Pedra, papel, tesoura, lagarto, Spock. Eh muito simples! Olhe - tesoura corta papel, papel cobre pedra, pedra esmaga lagarto, lagarto envenena Spock, Spock esmaga tesoura, tesoura decapita lagarto, lagarto come papel, papel refuta Spock, Spock vaporiza pedra e como sempre, pedra quebra tesoura...";
    cout<<"String de exemplo no trabalho:"<<endl;
    cout<<teste<<endl<<endl;

    sMinusculo(teste);
    limpaString(teste);

	//Separando os tweets em palavras diferentes
	vector<Palavra>vPalavra;
	separaPalavras(teste, vPalavra); //Testei apenas com uma string por vez mas fucniona para todas
	//Imprimindo o vetor de palavras mais o hashing delas para ver se ficou tudo certo
	cout<<"-Vetor de palavras separadas da string e seus respectivos hashings-"<<endl;
	for (short p = 0;p<vPalavra.size();p++)
    {
        vPalavra[p].setHash(string_hash(vPalavra[p].getConteudo())%vPalavra.size());
        cout<<vPalavra[p].getConteudo()<<" - " <<vPalavra[p].getHash()<<endl;
    }

    //Calculando a frequencia de todas as palavras (nao sei se tem um jeito melhor, provavelmente tem)
    for(int m = 0; m<vPalavra.size();m++)
    {
        for(int n=0;n<vPalavra.size();n++)
        {
            if(vPalavra[m].getHash() == vPalavra[n].getHash())
                vPalavra[m].aumentaFreq();
        }
    }

    short n = 6; //Testando o top6 palavras (de acordo com o exemplo)
    vector<Palavra>topPalavras(6);
    //Calculando as palavras mais usadas (provavelmente tem um jeito melhor de fazer isso tbm)
    for(int u=0;u<vPalavra.size();u++)
    {
        if(u==0)
        {
            short l = 0;
            while(l<n)
            {
            topPalavras[l] = vPalavra[0];
            l++;
            }
        }
        else
        {
            short l2 = 0;
            while(l2<n)
            {
                if(vPalavra[u].getFreq() > topPalavras[l2].getFreq())
                    topPalavras[l2] = vPalavra[u];
                l2++;
            }
        }
    }

    //Imprimindo as palavras mais usadas
    for(short b=0;b<n;b++)
    {
        cout<<topPalavras[b].getFreq()<<" - "<<topPalavras[b].getConteudo()<<endl;
    }

	//system("pause");
	return 0;
}
