/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Huffman.h"

/*Construtor*/
Huffman::Huffman()
{
	priLista = NULL;
	ultLista = NULL;
}

/*Destrutor*/
Huffman::~Huffman()
{
	deletaNo(priLista);
}

/*
FUNCAO DELETANO
Entrada: Primeiro No da lista
Saida: Todos os Nos deletados
Obs: Funcao auxiliar do destrutor
*/
void Huffman::deletaNo(NoH* n)
{
	if (n != NULL)
	{
		deletaNo(n->getDir());
		deletaNo(n->getEsq());
		delete n;
	}
}

/*
FUNCAO INSERE
Entrada: O caracter a ser inserido e a frequencia
Saida: O caracter inserido ao final da lista ou a sua frequencia aumentada caso o mesmo ja exista na lista
*/
void Huffman::insere(char c, int f)
{

	if (priLista == NULL)
	{
		priLista = new NoH();
		priLista->setChar(c);
		priLista->setFreq(f);
		ultLista = priLista;
	}
	else
	{
		/*Caminha na lista ate achar o caractere*/
		NoH *aux = priLista;                                                 
		while (aux != NULL && aux->getChar() != c)
			aux = aux->getProx();

		/*Verifica se o caractere foi encontrado ou nao
		Se foi encontrado, apenas aumenta a frequencia
		Se nao, cria um novo No e adiciona no final da lista*/
		if (aux != NULL)
			aux->setFreq(aux->getFreq() + f);
		else
		{
			ultLista->setProx(new NoH());
			ultLista = ultLista->getProx();
			ultLista->setChar(c);
			ultLista->setFreq(f);
		}
	}
}

/*
FUNCAO GETMENOR
Entrada: - 
Saida: O No de menor frequencia da lista
*/
NoH* Huffman::getMenor()
{
	NoH *aux = priLista;
	NoH *menor = priLista;

	/*Verifica se a lista possui apenas um elemento.
	 Se sim, ele mesmo sera o menor e entao sera retirado da lista e retornado
	 Se nao, caminha na lista ate achar o menor e realiza o mesmo processo
	*/
	if (aux->getProx() == NULL)
	{
		removeLista(aux);                               
		return aux;
	}
	else
	{
		while (aux != NULL)
		{
			if (aux->getFreq() < menor->getFreq())
				menor = aux;
			aux = aux->getProx();
		}
	}

	if (menor != NULL)
	{                                   
		removeLista(menor);
	}
	return menor;                                        
}

/*
FUNCAO CRIAARVORE
Entrada: -
Saida: Arvore de Huffman construida
*/
void Huffman::criaArvore()
{ 
	NoH *aux = NULL;
	/*	Cria Nos de Huffman de acordo com a seguintes caracteristicas:
	Filho a esquerda eh o No com menor frequencia
	Filho a direita eh o No com a segunda menor frequencia
	A frequencia do No pai eh a frequencia de seus dois filhos*/
	while (priLista != NULL)
	{
		aux = new NoH();
		aux->setEsq(getMenor());
		aux->setDir(getMenor());
		aux->setFreq(aux->getDir()->getFreq() + aux->getEsq()->getFreq());
		ultLista->setProx(aux);
		ultLista = aux;
	}
	priLista = aux;
}

/*
FUNCAO REMOVELISTA
Entrada: No a ser retirado
Saida: Lista sem o No
*/
void Huffman::removeLista(NoH *n)
{

	NoH* aux = priLista;
	/*Verifica se o No a ser retirado eh o primeiro da lista
	Se sim, retira o mesmo da lista e atualiza
	Se nao, percorre a lista e faz o mesmo processo*/
	if (n == aux)
		priLista = aux->getProx();

	else
	{
		while (aux->getProx() != n)
			aux = aux->getProx();
		aux->setProx(n->getProx());
		if (n->getProx() == NULL)
			ultLista = aux;
	}
}

/*
FUNCAO CODIFICA
Entrada: String a ser codificada
Saida: Codigo da string e tabela de frequencias
*/
string Huffman::codifica(string s)
{
	/*Codifica uma unica string (Huffman estatico)*/
	string codigo;
	if (priLista == NULL)
	{
		/*Insere os caracteres da string na tabela de frequencias*/
		string::iterator it;
		it = s.begin();
		while (it != s.end())
		{
			insere(*it, 1);
			it++;
		}
		criaArvore(); //Cria a arvore
		geraCodigo(codigo, priLista); //Gera os codigos da arvore
		return geraCodigoString(s); //Gera o codigo da string
	}
	else
		cout << "Tabela de frequencias e arvore de Huffman ja foram criadas, nao eh possivel adicionar uma nova string." << endl;
	return codigo;
}

/*
FUNCAO GETARVORE
Entrada: -
Saida: Ponteiro para o primeiro No da lista (raiz da arvore)
*/
NoH** Huffman::getArvore()
{
	return &priLista;
}

/*
FUNCAO GERACODIGO
Entrada: String a ser codificada e No da lista
Saida: Tabela de codigos
*/
void Huffman::geraCodigo(string s, NoH *n)
{
	if (n != NULL)
	{
		if (n->getChar() != -1)
		{
			if (n->getChar() >= 97 && n->getChar() <= 122)
			{
				codigos[n->getChar() - 97] = s;
			}
		}
		else
		{
			/*Coloca 1 para os Nos a direita e 0 para os nos a esquerda*/
			if (n->getDir() != NULL)
			{
				s.push_back('1');
				geraCodigo(s, n->getDir());
				s.erase(s.end() - 1);
			}
			if (n->getEsq() != NULL)
			{
				s.push_back('0');
				geraCodigo(s, n->getEsq());
				s.erase(s.end() - 1);
			}
		}
	}
}

/*
FUNCAO GERACODIGOSTRING
Entrada: String para gerar o codigo
Saida: Codigos presentes na arvore que formam a string
*/
string Huffman::geraCodigoString(string s)
{
	string *codigo = new string;
	string::iterator it = s.begin();
	while (it != s.end())
	{
		if (*it >= 97 && *it <= 122)
		{
			*codigo += codigos[*it - 97];
		}
		it++;
	}
	return *codigo;
}