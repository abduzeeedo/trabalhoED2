/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef NO_H
#define NO_H
#include <iostream>
#include "Tweet.h"

using namespace std;
class No
{
public:
	No();
	No* getEsq();
	No* getDir();
	int getFB();
	Tweet* getChave();
	void setEsq(No* esq);
	void setDir(No* dir);
	void setFB(int fb);
	void setChave(Tweet* chave);
	virtual ~No();

protected:

private:
	Tweet* chave;
	int fatorBalanceamento;
	No* esq;
	No* dir;
};

#endif // NO_H