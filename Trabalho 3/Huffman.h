/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "NoH.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Huffman
{
public:
	Huffman();
	string codifica(string s); //Codifica uma string
	double getTempoGasto(); //Retorna o tempo gasto na codificacao
	~Huffman();
private:
	double tempoGasto; //Tempo gasto para codificacao da string
	NoH *priLista; //Primeiro No da lista
	NoH *ultLista; //Ultimo No da lista
	NoH* getMenor(); //Menor No da lista
	void removeLista(NoH* n); //Remove um no da lista
	void insere(char c, int f); //Insere o char C
	void criaArvore(); //Constroi arvore de Huffman
	string geraCodigoString(string s); //Gera o codigo da string usando a arvore
	void geraCodigo(string s, NoH* n); //Pega todos os codigos presentes na arvore
	string codigos[26]; //Lista de caracteres minusculos
	void deletaNo(NoH* n); //Deleta um no da Arvore
};
#endif // HUFFMAN_H