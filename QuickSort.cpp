#include "QuickSort.h"
#include "InsertionSort.h"
using namespace std;

/*
ainda falta:
escrever mais comentarios
implementar a funcao para ler do arquivo entrada.txt para fazer a ordena�ao aleatoria dos Tweet
implementar a funcao para escrever os resultados no arquivo saida.txt
alterar o codigo para funcionar no numero N de vezes lidos da entrada.txt
*/

//Construtor
QuickSort::QuickSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
QuickSort::~QuickSort()
{
}

//Retorna o numero de trocas feitas
int QuickSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int QuickSort::getNumComparacoes()
{
	return numCompar;
}

double QuickSort::getTempoGasto()
{
	return tempoGasto;
}

//Nao usei o std::swap para poder adicionar o de numero de trocas
void QuickSort::troca(Tweet* &t1, Tweet* &t2)
{
	if (t1 != t2) //Nao troca se t1 e t2 sao iguais, ja que nao precisa
	{
		//uso isso so pra testar, nao precisa. vou tirar quando tiver tudo pronto 100%
		//cout << "trocando " << t1->getTweetID() << " por " << t2->getTweetID() << endl;
		Tweet* aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}

//Algoritmo de particionamento do vetor
int QuickSort::particiona(Tweet* vet[], int inicio, int fim, int pos)
{
	int pospiv;
	/*
	Posicao do vetor, a formula para calcular a posiçao é (inicio + ((posicao)%(fim-inicio+1))). No caso, posicao = (inicio + fim) / 2), metade do vetor
	Exemplo, caso queira passar a posicao 3 do vetor como pivo int pospiv = inicio + (3 % (fim - inicio + 1));
	Pode alterar tambem para ficar como parametro recebido da funcao exemplo indPivo (indice do vetor que deve ser usado como pivo), nesse caso ficaria
	int pospiv = inicio + (indPivo % (fim - inicio + 1))
	*/
	if (pos == -1) { //Pos com Codigo -1: Usa a posicao central do vetor como pivo
		pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	}
	else { //Caso Contratio, utiliza a posicao passada por parametro
		pospiv = inicio + (pos % (fim - inicio + 1));
	}

	int pivo = vet[pospiv]->getTweetID(); //Pega o tweetID da posicao que foi pedida e coloca ela como pivo
	troca(vet[pospiv], vet[fim]); // Coloca o pivo como o ultimo elemento do vetor
	pospiv = fim; //Volta a posicao do pivo como sendo o fim do vetor que vai ser particionado

				  //Variaveis para percorrer no vetor particionado
	int i = inicio - 1; //Comeca antes do inicio pq na primeira troca ele ja vai virar o inicio
	int j = inicio; //Anda do comeco ate o fim-1 do vetor

	while (j <= fim - 1) //Ele nao vai ate o fim do vetor pois o ultimo elemento eh o pivo que foi jogado para o final no comeco da execucao
	{
		if ((vet[j]->getTweetID() <= pivo) && ++numCompar)
		{
			i++;
			troca(vet[i], vet[j]);
		}
		j++;
	}

	troca(vet[i + 1], vet[pospiv]); //Coloca o elemento ja ordenado na ultima posicao do vetor particionado
	return i + 1;
}

//Algoritmo do quicksort recursivo
void QuickSort::quicksort(Tweet* vet[], int ini, int fim, char tipo)
{
	clock_t relogio;
	relogio = clock();
	if (tipo == 'r') { //QuickSort Recursivo Padrao
		if (ini < fim)
		{
			int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
			quicksort(vet, ini, part - 1, 'r');
			quicksort(vet, part + 1, fim, 'r');
		}
	}
	if (tipo == 'm') { //QuickSort Recursivo com Mediana de 3 valores
		if (ini < fim)
		{
			int posMediana = mediana(vet, 3, ini, fim);
			int part = particiona(vet, ini, fim, posMediana);
			quicksort(vet, ini, part - 1, 'm');
			quicksort(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'M') { //QuickSort Recursivo com Mediana de 5 valores
		if (ini < fim)
		{
			int posMediana = mediana(vet, 5, ini, fim);
			int part = particiona(vet, ini, fim, posMediana);
			quicksort(vet, ini, part - 1, 'm');
			quicksort(vet, part + 1, fim, 'm');
		}
	}

	if (tipo == 'i') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 10)
		if (ini < fim)
		{
			if (fim - ini <= 10) {
				InsertionSort ordena;
				ordena.insertionsort(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksort(vet, ini, part - 1, 'i');
				quicksort(vet, part + 1, fim, 'i');
			}
		}
	}

	if (tipo == 'I') { //QuickSort Recursivo Hibrido (com Insertion para particoes de tamanho menor ou igual a 100)
		if (ini < fim)
		{
			if (fim - ini <= 100) {
				InsertionSort ordena;
				ordena.insertionsort(vet, ini, fim + 1);
				numCompar = numCompar + ordena.getNumComparacoes();
				numTrocas = numTrocas + ordena.getNumTrocas();
			}
			else {
				int part = particiona(vet, ini, fim, -1); //Codigo -1 em pos: Particao usando posicao central do vetor como pivo
				quicksort(vet, ini, part - 1, 'I');
				quicksort(vet, part + 1, fim, 'I');
			}
		}
	}

	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

int QuickSort::mediana(Tweet* vet[], int numVal, int inicio, int fim) {

	int posMediana;//posicao a ser calculada e retornada da funcao
	int posRand;//Posicao Calculada Randomicamente
	if (numVal == 3) { //para k=3
		Tweet* vetor[3];
		for (int i = 0; i < 3; i++) {
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Tweet(posRand, vet[posRand]->getTweetID(), "", ""); //Atribui a USERID a posicao em si, e em tweetID o valor do tweetID contido nesta posicao
		}
		InsertionSort ordena;
		ordena.insertionsort(vetor, 0, 3);//utiliza o insertionSort para ordenar o TweetID do vetor de 3 posicoes
		posMediana = vet[1]->getUserID();//pega o valor central do vetor (mediana) e atribui o userID, que é a posicao original do vetor de tweets
		return posMediana;
	}

	if (numVal == 5) {//para k=5
		Tweet* vetor[5];
		for (int i = 0; i < 5; i++) {
			posRand = rand() % (fim - inicio); //Atribui a posicao randomica do vetor original
			vetor[i] = new Tweet(posRand, vet[posRand]->getTweetID(), "", ""); //Atribui a USERID a posicao em si, e em tweetID o valor do tweetID contido nesta posicao
		}
		InsertionSort ordena;
		ordena.insertionsort(vetor, 0, 3);//utiliza o insertionSort para ordenar o TweetID do vetor de 3 posicoes
		posMediana = vet[2]->getUserID();//pega o valor central do vetor (mediana) e atribui o userID, que é a posicao original do vetor de tweets
		return posMediana;
	}
	
	return inicio; //caso nao entre em nenhuma condicao, passa a posicao inicial como valor

}