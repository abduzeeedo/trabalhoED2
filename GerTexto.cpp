#include "GerTexto.h"

//Construtor
GerTexto::GerTexto()
{
}

//Destrutor
GerTexto::~GerTexto()
{
}

//Carrega UM tweet aleatorio
//ENTRADA: Nome do arquivo a ser lido e a seed do gerador de numero aleatorio
//Saida: Objeto do tipo tweet contendo os dados de uma linha aleatoriamente buscada
Tweet *GerTexto::carregarTweet(string nome, int seed)
{
	string linha;
	int i = 0;
	srand(seed);
	int stop = rand() % 3000000; //Define um criterio de parada como sendo um numero aleatorio (com seed) entre 0 e o numero de linhas do arquivo 
	Tweet *tw = new Tweet();
	fstream arquivo;
	arquivo.open(nome, std::fstream::in);
	if (arquivo.is_open()) { //percorre as linhas do arquivo ate chegar no aleatorio gerado
		while (i < stop) {
			getline(arquivo, linha, '\t');
			getline(arquivo, linha, '\t');
			getline(arquivo, linha, '\t');
			getline(arquivo, linha);
			i++;
		}

		getline(arquivo, linha, '\t');
		tw->setUserID(stoi(linha));
		getline(arquivo, linha, '\t');
		tw->setTweetID(stoll(linha));
		getline(arquivo, linha, '\t');
		tw->setTweetText(linha);
		getline(arquivo, linha);
		tw->setDate(linha);
	}
	return tw;//retorna um tweet com tais valores recebidos do arquivo txt
}
void GerTexto::salvarSaida(string saida, string nome){
	fstream arquivo;
	arquivo.open(nome,std::fstream::out | std::fstream::app);
	if(arquivo.is_open()){
		arquivo << saida;
		arquivo << "\n";

	}
}
