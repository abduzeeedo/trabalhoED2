#include "GerTexto.h"

GerTexto::GerTexto()
{
}

GerTexto::~GerTexto()
{
}

int GerTexto:: numAle(unsigned int seed)
{
	unsigned int prox = seed;
	int result;

	prox *= 1103515245;
	prox += 12345;
	result = (unsigned int)(prox / 65536) % 2048;

	prox *= 1103515245;
	prox += 12345;
	result <<= 10;
	result ^= (unsigned int)(prox / 65536) % 1024;

	prox *= 1103515245;
	prox += 12345;
	result <<= 10;
	result ^= (unsigned int)(prox / 65536) % 1024;

	seed = prox;

	return result;
}

//Carrega UM tweet aleatorio
Tweet *GerTexto::carregarTweet(string nome, int seed)
{
	string linha;
	int i = 0;
	int stop = numAle(seed) % 80; //TROCAR PARA SER UM NUMERO ALEATORIO COM SEED E TBM SE DER, RECEBER O NUMERO PRA USAR NO % POR PARAMETRO
	Tweet *tw = new Tweet();
	fstream arquivo;
	arquivo.open(nome, std::fstream::in);
	if (arquivo.is_open()) {
		while (i < stop) {
			getline(arquivo, linha, '\n');
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
	return tw;
}

//Carrega um vetor de tweets com numTweets tweets, os tweets sao carregados em sequencia
vector<Tweet*> GerTexto::carregaTweets(string nomeArquivo, int numTweets)
{
	fstream arquivo(nomeArquivo);
	vector<Tweet*> vTweets(numTweets);
	string linha;
	int t = 0;
	if (arquivo.is_open()) //Verifica se o arquivo esta aberto
	{
		while (!arquivo.eof() && t < numTweets) //Continua lendo o arquivo
		{
			Tweet *tw = new Tweet();
			getline(arquivo, linha, '\t');
			tw->setUserID(stoi(linha));
			getline(arquivo, linha, '\t');
			tw->setTweetID(stoll(linha));
			getline(arquivo, linha, '\t');
			tw->setTweetText(linha);
			getline(arquivo, linha);
			tw->setDate(linha);
			vTweets[t] = tw;
			t++;
		}
		arquivo.close(); //Fecha o arquivo
		return vTweets; //Retorna o vetor
	}
	else //Caso o arquivo nao esteja aberto, mostra um erro.
		cout << "Erro ao abrir arquivo de tweets " << nomeArquivo << endl;

}