/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/

#ifndef PALAVRA_H
#define PALAVRA_H
#include <string>
using namespace std;

class Palavra
{
private:
	string conteudo; //Palavra em si
	int frequencia; //Numero de vezes que a palavra aparece
	int numero_hash; //Numero do hashing da palavra
public:
	Palavra();
	Palavra(string, int); //Construtor sobrecarregado
	virtual ~Palavra();
	string getConteudo();
	void setConteudo(string);
	int getFreq();
	void setFreq(int);
	void aumentaFreq();
	void setHash(int);
	int getHash();
};
#endif // PALAVRA_H