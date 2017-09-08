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
	Tweet* carregarTweet(string nome, int seed);//Carrega um tweet aleatorio a partir de uma seed passada por parametro. Retorna o objeto tweet em si
	int numAle(unsigned int seed); //Funcao de geracao de numeros aleatorios com seed passada por parametro. Retorna um inteiro aleatorio a partir da seed.
	GerTexto(); //Construtor
	~GerTexto(); //Destrutor
};
#endif