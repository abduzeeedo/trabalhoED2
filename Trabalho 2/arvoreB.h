/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include <ctime>

#ifndef NO_B_H
#define NO_B_H
const int t = 2;   //Ordem da árvore
const int MAX = 2 * t;  //Número máximo de chaves
const int MIN = t;      //Número mínimo de chaves
class No_B
{
public:
	No_B() {
		/**
		*   Percorre todo o vetor de chaves, zerando os campos
		*   e atribuindo NULL aos ponteiros dos filhos
		*/
		for (int i = 0; i <= MAX; i++) {

			chave[i] = 0;
			filho[i] = NULL;

		}
		filho[MAX + 1] = NULL;    //O Número de filhos é uma unidade a mais que o número de chaves
		tamanho = 0;        //Como não há chaves então o tamanho é zero

	}
	~No_B() {}
	int getPos(int valor) {

		for (int i = 0; i < tamanho; i++) {

			if (chave[i] == valor) return i;

		}
		return -1;

	}//Retorna a posicao do 'valor' no vetor chave.
	int tamanho;
	int chave[MAX + 1]; // Para facilitar, os nós permitem uma chave a mais (buffer na posição MAX).
	No_B * filho[MAX + 2];
};

#endif // NO_B_H

class ArvoreB
{
private:
	No_B *raiz;
	void insereNo(No_B* no, int valor);
	void insereRecursivo(No_B* no, int valor);
	int split(No_B* n, No_B** novoNo);
	void deletaArvore(No_B* n);
	No_B* getPai(No_B* n);                  //Retorna o pai de um nó
	No_B* getPredecessor(int valor);        //Retorna um ponteiro pro predecessor
	No_B* getSucessor(int valor);           //Retorna um ponteiro pro sucessor
	void auxRemover(int valor, No_B* n);
	long int numCompar;
	long int numCopias;
	double tempoGastoInsercao;
	double tempoGastoRemocao;
public:
	No_B* buscar(int valor, No_B* n);
	void inserir(int valor);
	void remover(int valor);
	bool buscar(int valor);
	void limparArvore();
	void lerRaiz();
	long int getNumCompar();
	long int getNumCompias();
	double getTempoInsercao();
	double getTempoRemocao();
	/** Para testar os ponteiros*/
	void testePai(int valor);
	void testePredecessor(int valor);
	void testeSucessor(int valor);
	int predecessor(int valor);             //Retorna o elemento predecessor de outro elemento;
	int sucessor(int valor);                //Retorna o elemento sucessor de outro elemento;
	int sucessorNaRaiz(int valor);
	ArvoreB();
	No_B** getRaiz();
	~ArvoreB();
};
#endif // ARVOREB_H_INCLUDED