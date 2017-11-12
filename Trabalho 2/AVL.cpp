/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "AVL.h"
//construtor e destrutor
AVL::AVL()
{
	raiz = NULL;
	numCompar = 0;
	numCopias = 0;
	tempoGastoInsercao = 0;
	tempoGastoRemocao = 0;
	tempoGastoBusca = 0;
}

AVL::~AVL()
{
	destrutorAux(raiz);
}
void AVL::destrutorAux(No *no)
{
	if (no != NULL)
	{
		destrutorAux(no->getEsq());
		destrutorAux(no->getDir());
		delete no;
	}
}
//rotacoes
No *AVL::rotR(No *no) //rotacao direita
{
	No *noAux = no->getEsq();
	numCopias++;
	no->setEsq(noAux->getDir());
	noAux->setDir(no);
	return noAux;
}

No *AVL::rotRR(No *no) //rotacao dupla direita
{
	no->setEsq(rotL(no->getEsq()));
	No *noAux = rotR(no);
	numCopias++;
	return noAux;
}

No *AVL::rotL(No *no) //rotacao esquerda
{
	No *noAux = no->getDir();
	No *noAux2 = noAux->getEsq();
	numCopias++;
	numCopias++;
	no->setDir(noAux2);
	noAux->setEsq(no);
	return noAux;
}

No *AVL::rotLL(No *no) //rotacao dupla esquerda
{
	no->setDir(rotR(no->getDir()));
	No *noAux = rotL(no);
	numCopias++;
	return noAux;
}
//Buscas
bool AVL::busca(int tweetId)
{
	return buscaAuxiliar(tweetId, raiz);
}
bool AVL::buscaAuxiliar(int tweetId, No *no)
{
	clock_t relogio;
	relogio = clock();

	if (no == NULL)
	{
		numCompar++;
		tempoGastoBusca += (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return false;
	}
	else if (no->getChave()->getTweetID() == tweetId)
	{
		numCompar++;
		tempoGastoBusca += (clock() - relogio) / (double)CLOCKS_PER_SEC;
		return true;
	}
	else if (no->getChave()->getTweetID() != tweetId)
	{
		if (no->getEsq() != NULL && no->getChave()->getTweetID() < tweetId)
		{
			numCompar++;
			return buscaAuxiliar(tweetId, no->getEsq());
		}
		else if (no->getDir() != NULL && no->getChave()->getTweetID() > tweetId)
		{
			numCompar++;
			return buscaAuxiliar(tweetId, no->getDir());
		}
		else if (no->getEsq() == NULL && no->getDir() == NULL)
		{
			numCompar++;
			tempoGastoBusca += (clock() - relogio) / (double)CLOCKS_PER_SEC;
			return false;
		}
	}
}

//Manipulacao da arvore
void AVL::inserir(Tweet *tw)
{
	clock_t relogio;
	relogio = clock();
	inserirAuxiliar(tw, raiz);
	raiz = balanceia(raiz);
	calculaFB(raiz);
	tempoGastoInsercao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}
void AVL::remover(Tweet *tw)
{
	clock_t relogio;
	relogio = clock();
	raiz = removerAux(raiz, tw);
	raiz = balanceia(raiz);
	calculaFB(raiz);
	tempoGastoRemocao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}
No *AVL::removerAux2(No *no)
{
	No *noAux;
	No *noAuxPai = new No();
	if ((no->getEsq() == NULL) && (no->getDir() == NULL))
	{
		numCompar++;
		delete no;
		return NULL;
	}
	else if ((no->getEsq() == NULL) && (no->getDir() != NULL))
	{
		numCompar++;
		noAux = no->getEsq();
		numCopias++;
		delete no;
		return noAux;
	}
	else if ((no->getEsq() != NULL) && (no->getDir() == NULL))
	{
		numCompar++;
		noAux = no->getDir();
		numCopias++;
		delete no;
		return noAux;
	}
	else
	{
		if (no->getEsq()->getDir() == NULL)
		{
			numCompar++;
			noAux = no->getEsq();
			numCopias++;
			no->getEsq()->setDir(no->getDir());
			delete no;
			delete noAux;
		}
		else
		{
			noAux = no->getEsq();
			numCopias++;
			while (noAux->getDir() != NULL)
			{
				noAuxPai = noAux;
				numCopias++;
				noAux = noAux->getDir();
				numCopias++;
			}
			if (noAux->getEsq() != NULL){
			numCompar++;
				noAuxPai->setDir(noAux->getEsq());
			}
			else
			{
				noAuxPai->setDir(NULL);
			}
			noAux->setDir(no->getDir());
			noAux->setEsq(no->getEsq());
			delete no;
			return noAux;
		}
	}
	return NULL;
}
No *AVL::removerAux(No *no, Tweet *tw)
{
	No *noAux = no;
	numCopias++;
	No *noPai = new No();
	bool bdir = false;
	if (tw->getTweetID() == no->getChave()->getTweetID()){

		numCompar++;
		return removerAux2(noAux);
	}
	while (noAux != NULL)
	{
		if (tw->getTweetID() == noAux->getChave()->getTweetID())
		{
			numCompar++;
			if (bdir)
				noPai->setDir(removerAux2(noAux));
			else
				noPai->setEsq(removerAux2(noAux));
			return no;
		}
		else
		{
			if (tw->getTweetID() > noAux->getChave()->getTweetID())
			{
				numCompar++;
				bdir = false;
				noPai = noAux;
				numCopias++;
				noAux = noAux->getEsq();
				numCopias++;
			}
			else
			{
				numCompar++;
				bdir = true;
				noPai = noAux;
				numCopias++;
				noAux = noAux->getDir();
				numCopias++;
			}
		}
	}
	return no;
}
void AVL::inserirAuxiliar(Tweet *tw, No *no)
{
	if (no == NULL)
	{
		numCompar++;
		no = new No();
		no->setChave(tw);
		numCopias++;
	}
	else
	{
		if (tw->getTweetID() < no->getChave()->getTweetID())
		{
			numCompar++;
			inserirAuxiliar(tw, no->getEsq());
		}

		else if (tw->getTweetID() > no->getChave()->getTweetID())
		{
			numCompar++;
			inserirAuxiliar(tw, no->getDir());
		}
	}
}
void AVL::limpaDados()
{
	numCompar = 0;
	numCopias = 0;
	tempoGastoInsercao = 0;
	tempoGastoRemocao = 0;
}

//Outras funcoes
void AVL::calculaFB(No *no)
{
	if (no != NULL)
	{
		no->setFB(((calculaAltura(no->getEsq())) - (calculaAltura(no->getDir()))));
		numCompar++;
	}
}
int AVL::calculaAltura(No *no)
{
	int altEsq, altDir;
	if (no == NULL)
	{
		numCompar++;
		return 0;
	}
	else
	{
		altEsq = calculaAltura(no->getEsq());
		altDir = calculaAltura(no->getDir());
		if (altEsq > altDir)
		{
			numCompar++;
			return (1 + altEsq);
		}
		else
		{
			numCompar++;
			return (1 + altDir);
		}
	}
}
No *AVL::balanceia(No *no)
{
	if (no != NULL)
	{
		calculaFB(no);
		if (no->getFB() == 2)
		{
			numCompar++;
			calculaFB(no->getEsq());
			if (no->getEsq()->getFB() > 0)
			{
				numCompar++;
				no = rotR(no);
				numCopias++;
			}

			else
			{
				numCompar++;
				no = rotRR(no);
				numCopias++;
			}
		}
		else if (no->getFB() == -2)
		{
			calculaFB(no->getDir());
			if (no->getDir()->getFB() < 0)
			{
				numCompar++;

				no = rotL(no);
				numCopias++;
			}
			else
			{
				no = rotLL(no);
				numCompar++;
				numCopias++;
			}
		}
		no->setEsq(balanceia(no->getEsq()));
		no->setDir(balanceia(no->getDir()));
	}
	return no;
}
void AVL::imprimir()
{
	imprimirAux(raiz);
}
void AVL::imprimirAux(No *no)
{
	if (no != NULL)
	{
		cout << "Chave: " << no->getChave()->getTweetID() << endl;
		if (no->getEsq() != NULL)
			cout << "Esquerda: " << no->getEsq()->getChave()->getTweetID() << endl;
		else
			cout << "Esquerda: NULL" << endl;
		if (no->getDir() != NULL)
			cout << "Direita: " << no->getDir()->getChave()->getTweetID() << endl;
		else
			cout << "Direita: NULL" << endl;
		cout << endl;
		imprimirAux(no->getEsq());
		imprimirAux(no->getDir());
	}
}
long int AVL::getNumCompar()
{
	return numCompar;
}
long int AVL::getNumCopias()
{
	return numCopias;
}
double AVL::getTempoInsercao()
{
	return tempoGastoInsercao;
}
double AVL::getTempoRemocao()
{
	return tempoGastoRemocao;
}
double AVL::getTempoBusca()
{
	return tempoGastoBusca;
}
