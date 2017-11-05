/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "ArvoreSplay.h"

using namespace std;

/*
Struct para o No da arvore
*/
struct No
{
	Tweet* chave; //Chave do no
	struct No* esq; //Ponteiro para no a esquerda
	struct No* dir; //Ponteiro para no a direita
};

/*
Construtor da Arvore Splay
*/
ArvoreSplay::ArvoreSplay()
{
	numCompar = 0;
	numCopias = 0;
	tempoGastoInsercao = 0.0;
	tempoGastoRemocao = 0.0;
	raiz = NULL;
}

/*
Destrutor da Arvore Splay
*/
ArvoreSplay::~ArvoreSplay()
{
	deletaArvore(raiz);
	raiz = NULL;
}

/*
Funcao auxiliar para o destrutor
*/
void ArvoreSplay::deletaArvore(No* del)
{
	if (del != NULL)
	{
		deletaArvore(del->esq);
		deletaArvore(del->dir);
		delete del;
	}
}

/*
Funcao para retornar o ponteiro para a raiz da arvore
ENTRADA: -
SAIDA: Ponteiro para No (raiz)
*/
No* ArvoreSplay::getRaiz()
{
	return raiz;
}

/*
Funcao para retornar o numero de comparacoes feitas
ENTRADA: -
SAIDA: Numero de comparacoes
*/
long int ArvoreSplay::getnumCompar()
{
	return numCompar;
}

/*
Funcao para retornar o numero de copias de registro feitas
ENTRADA: -
SAIDA: Numero de copias de registro
*/
long int ArvoreSplay::getnumCopias()
{
	return numCopias;
}

/*
Funcao para retornar o tempo gasto nas insercoes
ENTRADA: -
SAIDA: Tempo gasto nas insercoes
*/
double ArvoreSplay::gettempoInsercao()
{
	return tempoGastoInsercao;
}

/*
Funcao para retornar o tempo gasto na remocao
ENTRADA: -
SAIDA: Tempo gasto na remocao
*/
double ArvoreSplay::gettempoRemocao()
{
	return tempoGastoRemocao;
}

/*
Funcao de rotacao para a esquerda
ENTRADA: No a ser rotacionado
SAIDA: Ponteiro para No com a rotacao feita
*/
No* ArvoreSplay::rotacaoEsq(struct No* x)
{
	struct No* y = x->dir;
	x->dir = y->esq;
	y->esq = x;
	numCopias++;
	return y;
}

/*
Funcao de rotacao para a direita
ENTRADA: No a ser rotacionado
SAIDA: Ponteiro para No com a rotacao feita
*/
No* ArvoreSplay::rotacaoDir(struct No* x)
{
	struct No* y = x->esq;
	x->esq = y->dir;
	y->dir = x;
	numCopias++;
	return y;
}

/*
Funcao para realizar o splay (espalhamento) de um No na arvore
ENTRADA: Ponteiro para o No raiz da arvore e chave a ser espalhada
SAIDA: Ponteiro para No raiz (o No que buscado, se existir. Caso contrario, retorna o ultimo No acessado)
*/
No* ArvoreSplay::splay(struct No* raiz, Tweet* chave)
{
	// Caso a raiz nao exista ou a chave seja a raiz, apenas retorna a raiz
	if (raiz == NULL || raiz->chave->getTweetID() == chave->getTweetID() && ++numCompar)
		return raiz;

	// Confere se a chave esta a direita da raiz
	if (raiz->chave->getTweetID() > chave->getTweetID() && ++numCompar)
	{
		if (raiz->esq == NULL)
			return raiz; // Se a raiz nao tem filho esquerdo, a chave nao existe - portanto retorna o ultimo no visitado (no caso, a raiz)

		// Verifica os casos de rotacao
		if (raiz->esq->chave->getTweetID() > chave->getTweetID() && ++numCompar) //Esquerda-esquerda
		{
			raiz->esq->esq = splay(raiz->esq->esq, chave); //Coloca a chave como raiz recursivamente
			raiz = rotacaoDir(raiz); //Faz a rotacao a direita na raiz
		}
		else if (raiz->esq->chave->getTweetID() < chave->getTweetID() && ++numCompar) //Esquerda-direita
		{
			raiz->esq->dir = splay(raiz->esq->dir, chave); //Coloca a chave como raiz recursivamente
			if (raiz->esq->dir != NULL)
				raiz->esq = rotacaoEsq(raiz->esq); //Faz a rotacao no filho esquerdo
		}

		// Faz a rotacao para a direita na raiz, caso necessario
		if (raiz->esq == NULL)
			return raiz;
		else
			return rotacaoDir(raiz);
	}
	else //Confere se a chave esta a direita da raiz
	{
		if (raiz->dir == NULL)
			return raiz; // Se a raiz nao tem filho direito a chave nao existe, portanto retorna o ultimo no visitado (no caso, a raiz)

		// Verifica os casos de rotacao
		if (raiz->dir->chave->getTweetID() > chave->getTweetID() && ++numCompar) //Direita-esquerda
		{
			raiz->dir->esq = splay(raiz->dir->esq, chave); //Coloca a chave como raiz recursivamente
			if (raiz->dir->esq != NULL)
				raiz->dir = rotacaoDir(raiz->dir); //Faz a rotacao a direita no filho a direita da raiz
		}
		else if (raiz->dir->chave->getTweetID() < chave->getTweetID() && ++numCompar) //Direita-direita
		{
			raiz->dir->dir = splay(raiz->dir->dir, chave); //Coloca a chave como raiz recursivamente
			raiz = rotacaoEsq(raiz); //Faz a rotacao a esquerda na raiz
		}

		// Faz a rotacao a esquerda na raiz, caso necessario
		if (raiz->dir == NULL)
			return raiz;
		else
			return rotacaoEsq(raiz);
	}
}

/*
Funcao de busca na arvore
ENTRADA: Chave do No a ser buscado
SAIDA: Ponteiro para o No encontrado
*/
No* ArvoreSplay::busca(Tweet* chave)
{
	return splay(raiz, chave);
}

/*
Funcao de impressao da arvore
ENTRADA: Ponteiro para o No raiz
SAIDA: Arvore impressa na tela
*/
void ArvoreSplay::imprimeArvore(No* raiz)
{
	if (raiz != NULL)
	{
		cout << "Chave: " << raiz->chave->getTweetID() << endl;
		if(raiz->esq != NULL)
			cout << "Esquerda: " << raiz->esq->chave->getTweetID() << endl;
		else
			cout << "Esquerda: NULL" << endl;
		if (raiz->dir != NULL)
			cout << "Direita: " << raiz->dir->chave->getTweetID() << endl;
		else
			cout << "Direita: NULL" << endl;
		cout << endl;
		imprimeArvore(raiz->esq);
		imprimeArvore(raiz->dir);
	}
}

/*
Funcao auxiliar para insercoes
ENTRADA: Chave do novo no
SAIDA: Ponteiro para o novo No (folha)
*/
No* ArvoreSplay::addNo(Tweet* ch)
{
	struct No* novoNo = new No();
	novoNo->chave = ch;
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	return novoNo;
}

/*
Funcao de insercao de um novo No na arvore
ENTRADA: Chave do novo No
SAIDA: Arvore com o novo No adicionado
*/
No* ArvoreSplay::insereNo(Tweet* chave)
{
	clock_t relogio;
	relogio = clock();

	// Caso 1 - A raiz nao existe (arvore vazia), o novo no e inserido como raiz da arvore
	if (raiz == NULL)
	{
		raiz = addNo(chave);
		tempoGastoInsercao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return raiz;
	}

	// Caso 2 - A chave ja existe na arvore
	raiz = splay(raiz, chave); // Faz o splay da chave (trazendo o no de valor mais perto (ou o proprio) para a raiz)
	if (raiz->chave == chave && ++numCompar) // Se a chave trazida pelo splay e a chave a ser inserida, apenas retorna a raiz - nao insere novamente
	{
		tempoGastoInsercao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return raiz;
	}

	// Caso 3 - A chave nao existe na arvore, logo, deve ser inserida
	struct No* novoNo = addNo(chave); //Cria um novo No para ser adicionado
	// Caso a chave do novo No seja menor que a chave da raiz, insere a direita e coloca o filho a esquerda da raiz como o filho esquerdo do novo No
	if (raiz->chave > chave && ++numCompar)
	{
		novoNo->dir = raiz;
		novoNo->esq = raiz->esq;
		raiz->esq = NULL;
	}
	// Caso a chave do novo No seja maior que a chave da raiz, insere a esquerda e coloca o filho a direita da raiz como o filho direito do novo No
	else
	{
		novoNo->esq = raiz;
		novoNo->dir = raiz->dir;
		raiz->dir = NULL;
	}
	tempoGastoInsercao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
	return raiz = novoNo; // Retorna a nova raiz da arvore
}

/*
Funcao de remocao de um No na arvore
ENTRADA: Chave do No a ser removido
SAIDA: Arvore com o novo No removido
*/
struct No* ArvoreSplay::removeNo(Tweet* chave)
{
	clock_t relogio;
	relogio = clock();

	// Caso 1 - A raiz nao existe (arvore vazia), nao e preciso fazer nenhuma remocao retorna a propria raiz (null)
	if (raiz == NULL)
	{
		tempoGastoRemocao = (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return raiz;
	}

	// Caso 2 - A chave nao existe na arvore
	raiz = splay(raiz, chave); // Faz o splay da chave (trazendo o no de valor mais perto (ou o proprio) para a raiz)  
	if (chave != raiz->chave)
	{
		tempoGastoRemocao = (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return raiz; // Se a chave trazida pelo splay nao e a chave que deve ser removida, apenas retorna a raiz - nao faz remocao
	}

	// Caso 3 - A chave existe na arvore e deve ser removida
	struct No* aux; //Cria um No auxiliar para remocao
	// Caso o No com a chave nao tenha filho a esquerda, coloca seu filho a direita como raiz
	if (!raiz->esq)
	{
		aux = raiz;
		raiz = raiz->dir;
	}
	// Caso o No com a chave tenha filho a esquerda, faz o splay deste filho com o No chave e o coloca na raiz e coloca o filho direito do No chave como filho direito da nova raiz
	else
	{
		aux = raiz;
		raiz = splay(raiz->esq, chave);
		raiz->dir = aux->dir;
	}

	//Faz a remocao do No auxiliar (No a ser removido)
	delete aux;

	//Retorna a nova raiz da arvore
	tempoGastoRemocao = (clock() - relogio) / (double)CLOCKS_PER_SEC;
	return raiz;
}
