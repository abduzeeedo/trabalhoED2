#include "GerTexto.h"

GerTexto::GerTexto()
{
}

GerTexto::~GerTexto()
{
}

//Carrega UM tweet aleatorio
Tweet *GerTexto::carregarTweet(string nome)
{
	string linha;
	int i=0;
	int stop = rand() % 80; //TROCAR PARA SER UM NUMERO ALEATORIO COM SEED E TBM SE DER, RECEBER O NUMERO PRA USAR NO % POR PARAMETRO
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