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
	Tweet* carregarTweet(string nome, int seed);
	vector<Tweet*> carregaTweets(string nomeArquivo, int numTweets);
	int numAle(unsigned int seed);
	GerTexto();
	~GerTexto();
};
#endif