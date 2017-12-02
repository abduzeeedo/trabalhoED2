/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef NOH_H
#define NOH_H
#include <stdlib.h>

class NoH
{
public:
	NoH() { esq = dir = prox = NULL; letra = -1; }
	~NoH() { esq = dir = prox = NULL; letra = -1; };
	char getChar() { return letra; }
	NoH *getEsq() { return esq; }
	NoH *getDir() { return dir; }
	NoH *getProx() { return prox; }
	int getFreq() { return freq; }
	void setEsq(NoH *n) { esq = n; }
	void setDir(NoH *n) { dir = n; }
	void setProx(NoH *n) { prox = n; }
	void setChar(char c) { letra = c; }
	void setFreq(int f) { freq = f; }

private:
	char letra; //Letra contida no No
	int freq; //Frequencia da letra
	NoH *esq; //Filho a esquerda
	NoH *dir; //Filho a direita
	NoH *prox; //Proximo No da lista
};
#endif // NOH_H
