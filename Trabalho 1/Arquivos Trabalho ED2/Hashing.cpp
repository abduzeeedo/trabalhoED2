/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Hashing.h"

#define INF -10000
Hashing::Hashing(int tamanho)
{
	//tamanho da tabela
	m = 2 * tamanho;
	table = new int[m];
	for (int i = 0; i < m; i++)
	{
		table[i] = INF;
	}
}
//Funcoes de hashing
int Hashing::divisao(int chave)
{
	return chave % m;
}
int Hashing::enlacamento(int chave)
{
	string str = to_string(chave);
	int enlacamento = 0;
	for (int i = 0; i < str.length(); i++)
	{
		enlacamento += atoi(str.substr(i, i + 1).c_str());
	}
	return enlacamento % m;
}
void Hashing::sondLinear(int chave, int hashingFunc)
{
	int posicao = 0;
	int i = 0, it = 0;
	int hk;
	bool posicaovazia = false;
	if (hashingFunc == 1)
		hk = divisao(chave);
	else if (hashingFunc == 2)
		hk = enlacamento(chave);
	while (!posicaovazia || it < 2)
	{
		posicao = (hk + i) % m;
		if (table[posicao] == INF)
		{
			posicaovazia = true;
			table[posicao] = chave;
		}
		else
		{
			i++;
			if (i >= m)
			{
				i = 0;
				it++;
			}
		}
	}
}
void Hashing::sondQuadratica(int chave, int hashingFunc)
{
	int posicao = 0;
	int i = 0, it = 0;
	int hk;
	bool posicaovazia = false;
	if (hashingFunc == 1)
		hk = divisao(chave);
	else if (hashingFunc == 2)
		hk = enlacamento(chave);
	while (!posicaovazia || it < 2)
	{
		posicao = (hk + i * i) % m;
		if (table[posicao] == INF)
		{
			posicaovazia = true;
			table[posicao] = chave;
		}
		else
		{
			i++;
			if (i >= m)
			{
				i = 0;
				it++;
			}
		}
	}
}
void Hashing::duploHash(int chave, int hashingFunc)
{
}
void Hashing::encadSeparado(int chave, int hashingFunc)
{
}
void Hashing::encadCol(int chave, int hashingFunc)
{
}
void Hashing::addVetor(int chave, int hashingFunc, int tratColis)
{
	int posicao = 0.0;
	if (hashingFunc == 1)
		posicao = divisao(chave);
	else if (hashingFunc == 2)
		posicao = enlacamento(chave);
	if (table[posicao] == INF)
		table[posicao] = chave;
	else
	{
		switch (tratColis)
		{
		case 1:
			sondLinear(chave, hashingFunc);
			break;
		case 2:
			sondQuadratica(chave, hashingFunc);
			break;
		case 3:
			duploHash(chave, hashingFunc);
			break;
		case 4:
			encadSeparado(chave, hashingFunc);
			break;
		case 5:
			encadCol(chave, hashingFunc);
			break;
		default:
			break;
			table[posicao] = chave;
		}
	}
}

Hashing::~Hashing()
{
	delete[] table;
}