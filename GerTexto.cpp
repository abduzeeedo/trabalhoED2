#include "GerTexto.h"

GerTexto::GerTexto()
{
}

GerTexto::~GerTexto()
{
}

Tweet *GerTexto::carregarTweet(string nome)
{
    string linha;
    Tweet *tw = new Tweet();
    fstream arquivo;
    arquivo.open(nome, std::fstream::in);
    if(arquivo.is_open()){
        getline(arquivo, linha, '\t');
        tw->setUserID(stoi(linha));
        getline(arquivo, linha, '\t');
        tw->setTweetID(atoi(linha.c_str()));
        getline(arquivo, linha, '\t');
        tw->setTweetText(linha);
        getline(arquivo, linha);
		tw->setDate(linha);
    }
return tw;
}

//Carrega um vetor de tweets com numTweets tweets
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
			tw->setTweetID(atoi(linha.c_str()));
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
		cout << "Erro ao abrir arquivo de tweets "<< nomeArquivo << endl;
}
