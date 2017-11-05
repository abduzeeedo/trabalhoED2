#ifndef NO_VP_H
#define NO_VP_H
#include <stdlib.h>
#include "Tweet.h"
#define VERMELHO 0
#define PRETO 1

class No_VP
{
public:

	No_VP(long long int v) {
		pai = NULL;
		proximo = NULL;
		anterior = NULL;
		cor = VERMELHO;
		valor = v;
	};
	~No_VP() {};
	No_VP* getProx() { return proximo; }
	No_VP* getAnt() { return anterior; }
	No_VP* getPai() { return pai; }
	long long int getValor() { return valor; }
	int getCor() { return cor; }
	void setProx(No_VP* p) { proximo = p; }
	void setAnt(No_VP* a) { anterior = a; }
	void setPai(No_VP* pa) { pai = pa; }
	void setValor(long long int v) { valor = v; }
	void setCor(int c) { cor = c; }
	No_VP* getAvo() {
		if (pai != NULL) {
			return pai->getPai();
		}
		return NULL;
	};
	No_VP* getTio() {
		No_VP* avo = getAvo();
		if (avo == NULL) {
			return NULL;
		}
		if (pai == avo->getAnt()) {
			return avo->getProx();
		}
		else {
			return avo->getAnt();
		}
	};

private:
	No_VP* proximo;
	No_VP* anterior;
	No_VP* pai;
	long long int valor;
	int cor;
};

#endif // NO_H
