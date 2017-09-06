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
int QuickSort::particiona(Tweet* vet[], int inicio, int fim)
{
	/*
	Posicao do vetor, a formula para calcular a posiçao é (inicio + ((posicao)%(fim-inicio+1))). No caso, posicao = (inicio + fim) / 2), metade do vetor
	Exemplo, caso queira passar a posicao 3 do vetor como pivo int pospiv = inicio + (3 % (fim - inicio + 1));
	Pode alterar tambem para ficar como parametro recebido da funcao exemplo indPivo (indice do vetor que deve ser usado como pivo), nesse caso ficaria
	int pospiv = inicio + (indPivo % (fim - inicio + 1))
	*/
	int pospiv = inicio + (((inicio + fim) / 2) % (fim - inicio + 1));
	int pivo = vet[pospiv]->getTweetID(); //Pega o tweetID da posicao que foi pedida e coloca ela como pivo
	troca(vet[pospiv], vet[fim]); // Coloca o pivo como o ultimo elemento do vetor
	pospiv = fim; //Volta a posicao do pivo como sendo o inicio do vetor que vai ser particionado

	//Variaveis para percorrer no vetor particionado
	int i = inicio - 1; //Comeca antes do inicio pq na primeira troca ele ja vai virar o inicio
	int j = inicio; //Anda do comeco ate o fim-1 do vetor

	while(j <= fim-1) //Ele nao vai ate o fim do vetor pois o ultimo elemento eh o pivo que foi jogado para o final no comeco da execucao
	{
		if ((vet[j]->getTweetID() <= pivo) && ++numCompar)
		{
			i++;
			troca(vet[i], vet[j]);
		}
		j++;
	}

	troca(vet[i + 1], vet[pospiv]);
	return i + 1;
}

//Algoritmo do quicksort recursivo
void QuickSort::quicksort(Tweet* vet[], int ini, int fim, char tipo)
{
	clock_t relogio;
	relogio = clock();
	if (tipo == 'r'){
		if (ini < fim)
		{
			int part = particiona(vet, ini, fim);
			quicksort(vet, ini, part - 1, 'r');
			quicksort(vet, part + 1, fim, 'r');
		}
	}
	if (tipo == 'm') {
		if (ini < fim)
		{
			int part = particionaMediana(vet, ini, fim);
			quicksort(vet, ini, part - 1, 'm');
			quicksort(vet, part + 1, fim, 'm');
		}
	}
	tempoGasto = (clock() - relogio) / (double)CLOCKS_PER_SEC;
}

// BRUNO DAQUI PRA BAIXO

/* BACKUP FUNCIONAL SEM O ULTIMO ELEMENTO
void QuickSort::QuickSortRandomAndMedian(Tweet* vet[], int start, int end) {
	int q;
	if (end - start<2) return;
	q = RandomAndMedianPartition(vet, start, end);
	QuickSortRandomAndMedian(vet, start, q);
	QuickSortRandomAndMedian(vet, q, end);
}

int QuickSort::RandomAndMedianPartition(Tweet* vet[], int p, int r) {
	int t;
	int x = vet[t = ((rand() % (r - p)) / 2) + p + (r - p) / 4]->getTweetID();
	int y = vet[t + 1]->getTweetID();
	int z = vet[t - 1]->getTweetID();
	int i = p - 1, j = r;
	if (y>x && y<z || y>z && y<x) x = y;
	else if (z>x && z<y || z>y && z<x) x = z;
	while (1) {
		do { j--; } while (vet[j]->getTweetID() > x);
		do { i++; } while (vet[i]->getTweetID() < x);
		if (i < j) troca(vet[i], vet[j]);
		else return j + 1;
	}
}
*/

int QuickSort::particionaMediana(Tweet* vet[], int inicio, int fim)
{
	//Seleciona o primeiro elemento do vetor como pivo (caso precise mudar o pivo, tem que mudar aqui e ali em baixo)
	int pivo = mediana(vet, 3, inicio, fim);
	//Pega o elemento imediatamente a direita do pivo, para caminhar da esquerda para direita. Caso precise mudar o pivo, tem que mudar esse calculo tbm
	int esq = pivo + 1;
	//Pega o ultimo elemento do vetor para caminhar da direita para esquerda
	int dir = fim;

	//Caminhando no vetor enquanto os ponteiros nao se cruzam
	while (esq != dir)
	{
		if (vet[esq]->getTweetID() <= pivo && ++numCompar)
		{
			esq++;//Caminha da esquerda para a direita
			numCompar++;
		}
		else
		{
			while ((esq != dir) && (pivo < vet[dir]->getTweetID() && ++numCompar))
			{
				numCompar++;
				dir--; //Caminha da direita para a esquerda
			}
			troca(vet[esq], vet[dir]); //Faz a troca
		}
	}

	if (vet[esq]->getTweetID() > pivo && ++numCompar)
	{
		esq--; //Volta
		numCompar++;
	}

	troca(vet[inicio], vet[esq]); //Se mudar o pivo, nao esquecer de mudar o pivo (vet[inicio]) nessa troca tambem
	return (esq); //Retorna a posi�ao ordenada
}

int QuickSort::mediana(Tweet* vet[], int numVal, int inicio, int fim) {

	if (numVal == 3) {

		int valores[3];
		valores[0] = rand() % fim;
		valores[1] = rand() % fim;
		valores[2] = rand() % fim;

		for (int i = 1; i < 3; i++) {
			int chave = valores[i]; //salva o valor atual do vet[i] na chave auxiliar
			int j = i - 1;

			/* Desloca os elementos anteriores a chave que sao maiores que ela 1 posicao a frente da sua posicao atual*/
			while (j >= 0 && (valores[j] > chave)) {
				valores[j + 1] = valores[j];
				j--;
			}
			valores[j + 1] = chave; //coloca o valor salvo da chave na posicao que "sobrou" antes dos valores maiores que a chave
		}
		return valores[1];
	}
	else return inicio;

}
