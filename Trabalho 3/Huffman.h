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
#include <fstream>
#include <bitset>

using namespace std;

class Huffman
{
public:
	Huffman();
	string codifica(string); //Codifica uma string
	double getTempoGasto(); //Retorna o tempo gasto na codificacao
	void salvaBinario(string, string);
	~Huffman();
private:
	double tempoGasto; //Tempo gasto para codificacao da string
	NoH *priLista; //Primeiro No da lista
	NoH *ultLista; //Ultimo No da lista
	NoH* getMenor(); //Menor No da lista
	void removeLista(NoH*); //Remove um no da lista
	void insere(char, int); //Insere o char C
	void criaArvore(); //Constroi arvore de Huffman
	string geraCodigoString(string); //Gera o codigo da string usando a arvore
	void geraCodigo(string, NoH*); //Pega todos os codigos presentes na arvore
	string codigos[26]; //Lista de caracteres minusculos
	void deletaNo(NoH*); //Deleta um no da Arvore
};
#endif // HUFFMAN_H