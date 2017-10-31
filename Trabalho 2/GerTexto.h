/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef GERTEXTO_H
#define GERTEXTO_H

#include <iostream>
#include <string>
#include <vector>
#include "Tweet.h"
#include <fstream>

using namespace std;

class GerTexto
{
private:
public:
	Tweet** carregaTweets(string nomeArquivo, int numTweets);//Faz a carga dos tweets do arquivo txt em um Vetor de objetos do tipo Tweet
	GerTexto(); //Construtor
	void salvarSaida(string saida, string nome);//Funcao que salva saida em um arquivo TXT
	~GerTexto(); //Destrutor
};
#endif