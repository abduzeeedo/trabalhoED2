/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

#include "Palavra.h"

Palavra::Palavra()
{
	//ctor
	frequencia = 0;
}

//Construtor sobrecarregado
Palavra::Palavra(string c, int f)
{
	conteudo = c;
	frequencia = f;
}

Palavra::~Palavra()
{
	//dtor
}

/*Gets e sets*/
string Palavra::getConteudo()
{
	return conteudo;
}

void Palavra::setConteudo(string c)
{
	conteudo = c;
}

int Palavra::getFreq()
{
	return frequencia;
}

void Palavra::setFreq(int f)
{
	frequencia = f;
}

void Palavra::aumentaFreq()
{
	frequencia++;
}