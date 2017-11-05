/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include <iostream>
#include <stdlib.h>
#include "arvoreB.h"

using namespace std;

ArvoreB::ArvoreB()
{
	raiz = NULL;
	numCompar = 0;
	numCopias = 0;
	tempoGastoInsercao = 0;
	tempoGastoRemocao = 0;
}

ArvoreB :: ~ArvoreB()
{
	deletaArvore(raiz);
}

void ArvoreB::deletaArvore(No_B* n)
{
	if (n == NULL)
		return;
	for (int i = 0; i <= n->tamanho; i++)
	{
		deletaArvore(n->filho[i]);
		delete n->filho[i];
	}
}

No_B** ArvoreB::getRaiz()
{
	return &raiz;
}

void ArvoreB::inserir(int valor)
{
	clock_t relogio;
	relogio = clock();

	//cout << "Inserindo o valor " << valor << endl;
	if (raiz == NULL && ++numCompar)
	{//Verifica se a arvore esta vazia, se sim, apenas cria a raiz
		raiz = new No_B();
		insereNo(raiz, valor);
	}
	else
	{//Caso contrario, chama a insercao
		++numCompar;
		insereRecursivo(raiz, valor);
		if (raiz->chave[MAX] != 0 && ++numCompar)
		{//Verifica se a raiz esta em overflow, se estiver faz o split
			No_B* novoNo;
			No_B* auxRaiz = new No_B();
			int s = split(raiz, &novoNo);
			auxRaiz->filho[0] = raiz;
			auxRaiz->filho[1] = novoNo;
			auxRaiz->chave[0] = s;
			auxRaiz->tamanho++; //Aumenta o identificador do número de filhos presente no nó
			raiz = auxRaiz;
		}
	}
	tempoGastoInsercao += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

void ArvoreB::insereNo(No_B* no, int valor)
{//Insere no 'no' o valor da variavel 'valor'
	int k = 0;
	while (k < no->tamanho && no->chave[k] < valor)
	{//Encontra a posicao do vetor de chaves que 'valor' sera inserido
		k++;
	}
	for (int i = no->tamanho - 1; i >= k; i--) 
	{//Desloca todos os valores a direita de k uma posicao, incluindo k, liberando espaco para valor ser inserido em k
		no->chave[i + 1] = no->chave[i];
	}
	for (int i = no->tamanho; i >= k; i--)
	{//Desloca todos os filhos a direita de k uma posicao, incluindo k, liberando espaco para outro filho ser inserido em k
		no->filho[i + 1] = no->filho[i];
	}
	no->chave[k] = valor;
	no->tamanho++;
}

void ArvoreB::insereRecursivo(No_B* no, int valor)
{
	int k = 0;
	while (k < no->tamanho)
	{//Encontra a posicao do vetor de chaves que 'valor' sera inserido
		if (no->chave[k] < valor)k++;
		else break;
	}
	if (no->filho[k] == NULL)
	{//Verifica se o no eh folha, se for, insere, caso contrario continua descendo na arvore
		insereNo(no, valor);
	}
	else
	{
		insereRecursivo(no->filho[k], valor);
		if (no->filho[k]->chave[MAX] != 0)
		{//Verifica se houve overflow na inserção
			No_B* novoNo;//No que sera criado no split
			int s = split(no->filho[k], &novoNo);//Valor de retorno do split, ou seja, o valor que será adicionado no 'no'
			insereNo(no, s);
			no->filho[no->getPos(s)] = no->filho[no->getPos(s) + 1];//Coloco o ponteiro para o filho 'n' usado no split na posicao correta
			no->filho[no->getPos(s) + 1] = novoNo;//Adiciona o 'novoNo' criado como filho maior de 's'
		}
	}
}

int ArvoreB::split(No_B* n, No_B** novoNo)
{//Reparte os valores de 'n' para o 'novoNo' e retorna o valor mediano;
	*novoNo = new No_B();

	int MID = MIN;//Encontro o valor mediano no No 'n'
	int k = 0;
	int sobressalente;

	for (int i = MID + 1; i <= MAX; i++)
	{//Transfiro os valores a direita de MID para o novo No.
		(*novoNo)->chave[k] = n->chave[i];
		n->chave[i] = 0;
		(*novoNo)->filho[k] = n->filho[i];
		n->filho[i] = NULL;
		(*novoNo)->tamanho++;
		n->tamanho--;
		k++;
		numCopias++;
	}

	(*novoNo)->filho[k] = n->filho[MAX + 1];
	n->filho[MAX + 1] = NULL;
	sobressalente = n->chave[MID];//Guardo o No que ira subir para o pai
	n->chave[MID] = 0;
	n->tamanho--;
	numCopias++;

	return sobressalente;//Retorno o No sobressalente da funcao split
}

No_B* ArvoreB::buscar(int valor, No_B* n)
{

	No_B* aux;
	if (n == NULL)
		return NULL;
	else
	{//Verifica se o valor esta no No 'n', se estiver, retona a posicao de memoria de 'n', caso nao esteja, verifica nos seus filhos
		if (n->getPos(valor) != -1)
			return n;
	}
	for (int i = 0; i <= n->tamanho; i++)
	{//Verifica se encontra o valor nos filhos de 'n'
		aux = buscar(valor, n->filho[i]);
		if (aux != NULL)
			return aux;
	}
	return NULL;
}

bool ArvoreB::buscar(int valor)
{
	if (buscar(valor, raiz) != NULL)
		return true;
	return false;
}

int ArvoreB::sucessorNaRaiz(int valor)
{                 /**Sucessor de um dado valor contido na raiz*/
	if (raiz != buscar(valor, raiz)) 
	{
		cout << "O elemento escolhido nao esta na raiz" << endl;
		return 0;
	}
	else 
	{
		int posicaoChave = raiz->getPos(valor);
		No_B* auxiliar = raiz->filho[posicaoChave + 1];       //Desce para o primeiro filho a direita -- possível sucessor
		if (auxiliar == NULL)
		{//O sucessor está na raiz
			if (raiz->chave[posicaoChave + 1] == 0)
			{
				cout << endl;
				cout << "O elemento nao possui sucessor" << endl;
				return 0;
			}
			else
				return raiz->chave[posicaoChave + 1];         //Retornando o sucessor
		}
		while (auxiliar->filho[0] != NULL)                     //Desce para a esquerda até uma folha
			auxiliar = auxiliar->filho[0];
		return auxiliar->chave[0];                          //Retorna o primeiro elemento que é o sucessor
	}
}

int ArvoreB::sucessor(int valor)
{//Retorna o valor do sucessor do elemento
	if (buscar(valor, raiz) == NULL)
	{
		cout << "O elemento escolhido nao esta presente na arvore B." << endl;
		return 0;
	}
	if (raiz != buscar(valor, raiz)) {
		No_B* elemento = buscar(valor, raiz);   //Busca na árvore e armazena um ponteiro pro nó do valor
		int posicaoChave = elemento->getPos(valor); //Armazena posição do valor chave
		if (elemento->filho[0] != NULL)
		{ //Não é folha
			elemento = elemento->filho[posicaoChave + 1];   //Desce para o filho direito da chave
			while (true) 
			{
				if (elemento->filho[0] == NULL)
				{  //Filho a esquerda da ultima chave válida
					return elemento->chave[0];
				}
				else
				{
					elemento = elemento->filho[elemento->tamanho];
				}
			}
		}
		else
		{   //Folha
			if (posicaoChave == (elemento->tamanho - 1))
			{    //ultimo elemento da folha
				No_B* pai = getPai(elemento);
				/**
				*   Corrige o problema de ter um nó intermediário a esquerda do primeiro nó da raiz
				*   O problema seria em retornar o sucessor do nó mais a direita do nó a esquerda da raiz
				*/
				if ((raiz->chave[raiz->tamanho - 1]<valor) && (pai->filho[pai->tamanho] == elemento))
				{
					cout << "Nao ha sucessor desse elemento porque ele eh o maior valor da arvore B." << endl;
					return 0;
				}
				if ((raiz->chave[0]>valor) && (pai->filho[pai->tamanho] == elemento)) 
				{   ///Pega elemento da raiz
					for (int i = 0; i < raiz->tamanho; i++)
					{
						if (raiz->chave[i + 1] == 0) {    //Se o elemento seguido for nulo retorna ele
							return raiz->chave[i];
						}
					}
				}
				for (int i = 0; i <= pai->tamanho; i++)
				{  //Percorre os filhos para saber
					if (pai->filho[i] == elemento)
					{
						return pai->chave[i];
					}
				}
			}
			else
			{
				return elemento->chave[posicaoChave + 1];
			}
		}
	}
	else 
	{                                                       //Elemento está na raiz
		int posicaoChave = raiz->getPos(valor);
		if (raiz->filho[0] == NULL) 
		{ //Só há raiz presente
			if ((raiz->chave[posicaoChave + 1]) == 0)
			{ //Sucessor do último elemento não há
				cout << "Nao ha sucessor do elemento " << valor << " na arvore B, pois ele eh o\nultimo elemento da arvore" << endl;
				return 0;
			}
			else
			{
				return raiz->chave[posicaoChave + 1];             //Elemento posterior
			}
		}
		else
		{ //Há mais nós além da raiz
			No_B* auxiliar = raiz->filho[posicaoChave + 1];       //Desce para o filho a direita
			while (true)
			{
				if (auxiliar->filho[0] == NULL)
				{//Filho a esquerda de uma folha
					return auxiliar->chave[0];
				}
				else
				{
					auxiliar = auxiliar->filho[0];              //caminha pra esquerda
				}
			}
		}
	}
}

No_B* ArvoreB::getSucessor(int valor)
{//Retorna o nó do sucessor do elemento
	if (buscar(valor, raiz) == NULL)
	{
		//cout << "O elemento escolhido nao esta presente na arvore B." << endl;
		return NULL;
	}
	if (raiz != buscar(valor, raiz)) 
	{
		No_B* elemento = buscar(valor, raiz);                   //Busca na árvore e armazena um ponteiro pro nó do valor
		int posicaoChave = elemento->getPos(valor);             //Armazena posição do valor chave
		if (elemento->filho[0] != NULL)
		{//Não é folha
			elemento = elemento->filho[posicaoChave + 1];         //Desce para o filho direito da chave
			while (true)
			{
				if (elemento->filho[0] == NULL)
				{                   //Filho a esquerda da ultima chave válida
					return elemento;
				}
				else
				{
					elemento = elemento->filho[elemento->tamanho];
				}
			}
		}
		else
		{//Folha
			if (posicaoChave == (elemento->tamanho - 1))
			{            //ultimo elemento da folha
				No_B* pai = getPai(elemento);
				/**
				*   Corrige o problema de ter um nó intermediário a esquerda do primeiro nó da raiz
				*   O problema seria em retornar o sucessor do nó mais a direita do nó a esquerda da raiz
				*/
				if ((raiz->chave[raiz->tamanho - 1]<valor) && (pai->filho[pai->tamanho] == elemento)) 
				{
					//cout << "Nao ha sucessor desse elemento porque ele eh o maior valor da arvore B." << endl;
					return NULL;
				}
				if ((raiz->chave[0]>valor) && (pai->filho[pai->tamanho] == elemento))
				{   //Pega elemento da raiz
					for (int i = 0; i < raiz->tamanho; i++)
					{
						if (raiz->chave[i + 1] == 0)
						{                 //Se o elemento seguido for nulo retorna ele
							return raiz;
						}
					}
				}
				for (int i = 0; i <= pai->tamanho; i++) 
				{//Percorre os filhos para saber
					if (pai->filho[i] == elemento)
					{
						return pai;
					}
				}
			}
			else
			{
				return elemento;
			}
		}
	}
	else 
	{ //Elemento está na raiz
		int posicaoChave = raiz->getPos(valor);
		if (raiz->filho[0] == NULL)
		{//Só há raiz presente
			if ((raiz->chave[posicaoChave + 1]) == 0)
			{ //Sucessor do último elemento não há
				//cout << "Nao ha sucessor do elemento " << valor << " na arvore B, pois ele eh o\nultimo elemento da arvore" << endl;
				return NULL;
			}
			else 
			{
				return raiz;
			}
		}
		else
		{ //Há mais nós além da raiz
			No_B* auxiliar = raiz->filho[posicaoChave + 1];       //Desce para o filho a direita
			while (true)
			{
				if (auxiliar->filho[0] == NULL)
				{                    //Filho a esquerda de uma folha
					return auxiliar;
				}
				else 
				{
					auxiliar = auxiliar->filho[0];              //caminha pra esquerda
				}
			}
		}
	}
}

void ArvoreB::testeSucessor(int valor)
{                        //Teste do ponteiro do sucessor
	cout << "Teste do sucessor: o sucessor do elemento " << valor << endl;
	No_B* p = getSucessor(valor);
	if (p != NULL)
		cout << "O no contem o elemento " << p->chave[0] << endl;
	else
		cout << "O elemento " << valor << " nao esta na arvore B." << endl;
}

int ArvoreB::predecessor(int valor)
{                             //Retorna o valor do predecessor do elemento
	if (buscar(valor, raiz) == NULL)
	{
		cout << "O elemento escolhido nao esta presente na arvore B." << endl;
		return 0;
	}
	if (raiz != buscar(valor, raiz))
	{
		No_B* elemento = buscar(valor, raiz);                   //Busca na árvore e armazena um ponteiro pro nó do valor
		int posicaoChave = elemento->getPos(valor);             //Armazena posição do valor chave
		if (elemento->filho[0] != NULL)
		{                           //Não é folha
			elemento = elemento->filho[posicaoChave];           //Desce para o filho esquerdo
			while (true)
			{
				if (elemento->filho[elemento->tamanho] == NULL) 
				{   //Filho a direita da ultima chave válida
					return elemento->chave[elemento->tamanho - 1];
				}
				else 
				{
					elemento = elemento->filho[elemento->tamanho];
				}
			}
		}
		else
		{                                                   //Folha
			if (posicaoChave == 0) 
			{                                //Primeiro elemento da folha
				No_B* pai = getPai(elemento);
				/**
				*   Corrige o problema de ter um nó intermediário a direita do primeiro nó da raiz
				*   O problema seria em retornar o predecessor do nó mais a esquerda do nó a direita da raiz
				*/
				if ((raiz->chave[0]>valor) && (pai->filho[0] == elemento))
				{
					cout << "Nao ha predecessor desse elemento porque ele eh o menor valor da arvore B." << endl;
					return 0;
				}
				else if ((raiz->chave[0]<valor) && (pai->filho[0] == elemento))
				{   //Pega elemento da raiz
					for (int i = 0; i < raiz->tamanho; i++) {
						if (raiz->chave[i + 1] == 0) {                  //Se o elemento seguido for nulo retorna ele
							return raiz->chave[i];
						}
					}
				}
				for (int i = 0; i <= pai->tamanho; i++)
				{           //Percorre os filhos para saber
					if (pai->filho[i] == elemento)
					{
						if (i>0)                                   //Ajusta o índice da chave
							i = i - 1;
						return pai->chave[i];
					}
				}
			}
			else
			{
				return elemento->chave[posicaoChave - 1];
			}
		}
	}
	else
	{                                                           //Elemento está na raiz
		int posicaoChave = raiz->getPos(valor);
		if (raiz->filho[0] == NULL)
		{                                   //Só há raiz presente
			if (posicaoChave == 0)
			{                                    //Predecessor do primeiro elemento não há
				cout << "Nao ha predecessor do elemento " << valor << " na arvore B, pois ele eh o\nprimeiro elemento da arvore" << endl;
				return 0;
			}
			else 
			{
				return raiz->chave[posicaoChave - 1];                 //Elemento anterior
			}
		}
		else 
		{                                                       //Há mais nós além da raiz
			No_B* auxiliar = raiz->filho[posicaoChave];             //Desce para o filho a esquerda
			while (true)
			{
				if (auxiliar->filho[auxiliar->tamanho] == NULL)
				{        //Filho a direita da ultima chave válida
					return auxiliar->chave[auxiliar->tamanho - 1];
				}
				else 
				{
					auxiliar = auxiliar->filho[auxiliar->tamanho];
				}
			}
		}
	}
}
No_B* ArvoreB::getPredecessor(int valor)
{                           //Retorna o nó do predecessor do elemento
	if (buscar(valor, raiz) == NULL)
	{
		//cout << "O elemento escolhido nao esta presente na arvore B." << endl;
		return NULL;
	}
	if (raiz != buscar(valor, raiz))
	{
		No_B* elemento = buscar(valor, raiz);                       //Busca na árvore e armazena um ponteiro pro nó do valor
		int posicaoChave = elemento->getPos(valor);                 //Armazena posição do valor chave
		if (elemento->filho[0] != NULL) 
		{//Não é folha
			elemento = elemento->filho[posicaoChave];               //Desce para o filho esquerdo
			while (true) 
			{
				if (elemento->filho[elemento->tamanho] == NULL)
				{       //Filho a direita da ultima chave válida
					return elemento;
				}
				else
				{
					elemento = elemento->filho[elemento->tamanho];
				}
			}
		}
		else
		{                                                       //Folha
			if (posicaoChave == 0)
			{                                    //Primeiro elemento da folha
				No_B* pai = getPai(elemento);
				/**
				*   Corrige o problema de ter um nó intermediário a direita do primeiro nó da raiz
				*   O problema seria em retornar o predecessor do nó mais a esquerda do nó a direita da raiz
				*/
				if ((raiz->chave[0]>valor) && (pai->filho[0] == elemento))
				{
					//cout << "Nao ha predecessor desse elemento porque ele eh o menor valor da arvore B." << endl;
					return NULL;
				}
				else if ((raiz->chave[0]<valor) && (pai->filho[0] == elemento))
				{   //Pega elemento da raiz
					for (int i = 0; i < raiz->tamanho; i++)
					{
						if (raiz->chave[i + 1] == 0)
						{                        //Se o elemento seguido for nulo retorna ele
							return raiz;
						}
					}
				}
				for (int i = 0; i <= pai->tamanho; i++)
				{                 //Percorre os filhos para saber
					if (pai->filho[i] == elemento)
					{
						if (i>0)                                         //Ajusta o índice da chave
							i = i - 1;
						return pai;
					}
				}
			}
			else
			{
				return elemento;
			}
		}
	}
	else
	{                                                               //Elemento está na raiz
		int posicaoChave = raiz->getPos(valor);
		if (raiz->filho[0] == NULL) 
		{                                       //Só há raiz presente
			if (posicaoChave == 0)
			{                                        //Predecessor do primeiro elemento não há
				//cout << "Nao ha predecessor do elemento " << valor << " na arvore B, pois ele eh o\nprimeiro elemento da arvore" << endl;
				return NULL;
			}
			else
			{
				return raiz;                                            //Elemento anterior
			}
		}
		else 
		{                                                           //Há mais nós além da raiz
			No_B* auxiliar = raiz->filho[posicaoChave];                 //Desce para o filho a esquerda
			while (true)
			{
				if (auxiliar->filho[auxiliar->tamanho] == NULL)
				{            //Filho a direita da ultima chave válida
					return auxiliar;
				}
				else 
				{
					auxiliar = auxiliar->filho[auxiliar->tamanho];
				}
			}
		}
	}
}

void ArvoreB::testePredecessor(int valor)
{                              //Teste do ponteiro do predecessor
	cout << "Teste do predecessor: o predecessor do elemento " << valor << endl;
	No_B* p = getPredecessor(valor);
	if (p != NULL)
		cout << "O no contem o elemento " << p->chave[0] << endl;
	else
		cout << "O elemento " << valor << " nao esta na arvore B." << endl;
}

void ArvoreB::remover(int valor)
{
	clock_t relogio;
	relogio = clock();

	if (buscar(valor, raiz) == NULL)
		cout << "A Arvore B esta vazia." << endl;
	cout << "Removendo o elemento " << valor << " ..." << endl;
	auxRemover(valor, buscar(valor, raiz));
	cout << "Elemento removido com sucesso." << endl;
	tempoGastoRemocao = (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

void ArvoreB::auxRemover(int valor, No_B* n)
{
	/**
	*   Precisa do sucessor e do predecessor
	*   Se o filho a direita e esquerda for NULL quer dizer que é folha, remove o elemento
	*   Se não atingiu um número mínimo de nós será necessário pegar o pai e o irmão,
	*   colocar em um vetor e fazer split
	*   ter um método chamado No_B* ArvoreB::getPai(No_B* n);  -> se for a raiz o pai é null, se não retorna um ponteiro pro nó pai
	*/
	if (n == NULL)
	{
		return;
	}
	if (n == raiz)
	{
		if (n->filho[0] == NULL) 
		{  //Só tem a raiz de nó
			int posicaoChave = n->getPos(valor);
			for (int i = 0; i<n->tamanho; i++)
			{
				if (i >= posicaoChave) 
				{
					n->chave[i] = n->chave[i + 1];
				}
				if (n->chave[0] == 0)
				{ //Arvore NULL
					raiz->tamanho = 0;  //Diminuindo o tamanho do número de chaves que estão presente
					raiz = NULL;
					return;
				}
			}
			n->tamanho--; //Como o elemento foi removido, então diminui-se o número de elementos presentes no nó
			return;
		}
		else {   //Tem mais de um nó na árvore
			No_B* pred = getPredecessor(valor); //predecessor
			No_B* suc = getSucessor(valor); //sucessor
			int posicaoChave = n->getPos(valor);
			if (pred->tamanho > suc->tamanho)
			{
				n->chave[posicaoChave] = pred->chave[pred->tamanho - 1];   //troca o elemento predecessor para o lugar do elemento a ser removido, e remove ele da folha
				pred->chave[pred->tamanho - 1] = 0;   //Apagando o elemento
				pred->tamanho--;    //Diminuindo o tamanho do número de chaves que estão presente
				return;
			}
			else {
				if (pred->tamanho == suc->tamanho){
				}
				if (pred->tamanho < suc->tamanho)
				{
					n->chave[posicaoChave] = suc->chave[0];   //troca o elemento predecessor para o lugar do elemento a ser removido, e remove ele da folha
					for (int i = 0; i<suc->tamanho; i++)
					{
						if (i >= posicaoChave)
						{
							suc->chave[i] = suc->chave[i + 1];
						}
					}
					suc->tamanho--;    //Diminuindo o tamanho do número de chaves que estão presente
					return;
				}
			}
		}
	}
	else if (n != raiz) {
	}
}

No_B* ArvoreB::getPai(No_B* n)
{ //Retorna o pai de um nó
	if (n == NULL)
	{  //Se o elemento procurado não estiver na árvore a busca pelo ponteiro será null, então o pai tbm é
		return NULL;
	}
	if (n == raiz)
	{  // Não tem pai
		return n;
	}
	else if (n != raiz) 
	{
		No_B* pai = raiz; //Para caminhar na árvore
		int elemento = n->chave[0];    //Para buscar na árvore
		while (true)
		{
			for (int i = 0; i < pai->tamanho; i++)
			{
				if (pai->chave[i] > elemento) 
				{   //Se a chave for maior que o elemento desço o pai para o ponteiro da esquerda
					if (pai->filho[i] == n)
					{
						return pai;
					}
					else 
					{   //Se o filho ainda não tem o elemento atualizo pai
						pai = pai->filho[i];    //atualiza o ponteiro do pai
						break;  //Sai do loop
					}
				}
				else if (pai->chave[i] < elemento)
				{
					if (pai->chave[i + 1] == 0)
					{ //Todos os elementos do nó são menores do que valor ==> Desço o pai para a direita no último ponteiro do filho
						if (pai->filho[i + 1] == n)
						{ //Se o ponteiro do último filho for igual a n, retorna o pai porque ele já foi encontrado
							return pai;
						}
						else
						{
							pai = pai->filho[i + 1];  //Desce pro último ponteiro de filho
							break;
						}
					}
				}
			}
		}
	}
}

void ArvoreB::testePai(int valor)
{  //Testar o ponteiro do pai
	cout << "Teste do pai: o pai do elemento " << valor << endl;
	No_B* p = getPai(buscar(valor, raiz));
	if (p != NULL)
		cout << "O no contem o elemento " << p->chave[0] << endl;
	else
		cout << "O elemento " << valor << " nao esta na arvore B." << endl;
}
void ArvoreB::limparArvore()
{
	cout << "Limpando a arvore B..." << endl;
	deletaArvore(raiz);
	raiz = NULL;        //Depois de limpar a estrutura o ponteiro deve ser atribuido como NULL, para poder limpar o desenho
	cout << "Estrutura limpa com sucesso" << endl;
}
void ArvoreB::lerRaiz()
{    //Procedimento para teste de verificação dos elementos da raiz
	for (int i = 0; i <= raiz->tamanho; i++) {
		cout << "i = " << i << "  " << raiz->chave[i] << endl;
	}
}

long int ArvoreB::getNumCompar()
{
	return numCompar;
}

long int ArvoreB::getNumCompias()
{
	return numCopias;
}

double ArvoreB::getTempoInsercao()
{
	return tempoGastoInsercao;

}

double ArvoreB::getTempoRemocao()
{
	return tempoGastoRemocao;
}