/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "GerTexto.h"

//Construtor
GerTexto::GerTexto()
{
}

//Destrutor
GerTexto::~GerTexto()
{
}
//Carrega um vetor de tweets com numTweets tweets, os tweets sao carregados em sequencia
//ENTRADA: Nome do arquivo de origem e numero de tweets que devem ser lidos
//SAIDA: Ponteiro para vetor de tweets contendo dados do arquivo txt.
Tweet** GerTexto::carregaTweets(string nomeArquivo, int numTweets)
{
	fstream arquivo(nomeArquivo);
	Tweet** ordenaEntrada = new Tweet*[numTweets];
	string linha;
	int t = 0;
	if (arquivo.is_open()) //Verifica se o arquivo esta aberto
	{
		while (!arquivo.eof() && t < numTweets) //Continua lendo o arquivo
		{
			int uID;
			long long int tID;
			string text, date;
			arquivo >> uID >> tID;
			std::getline(arquivo, linha, '\t');//Pega o espaco em branco, se tiver
			std::getline(arquivo, text, '\t');
			std::getline(arquivo, date);
			Tweet* tw = new Tweet(uID, tID, text, date);
			ordenaEntrada[t] = tw;
			t++;
			//cout << "tweet numero " << t << " carregado";
			//cout << endl;
		}
		arquivo.close(); //Fecha o arquivo
		return ordenaEntrada; //Retorna o vetor
	}
	else //Caso o arquivo nao esteja aberto, mostra um erro.
		cout << "Erro ao abrir arquivo de tweets " << nomeArquivo << endl;
}

//Funcao que salva saida em arquivo TXT
//ENTRADA: Dados a serem salvos na forma de String e nome do arquivo
//SAIDA: Dados Salvos no arquivo de saida .txt
void GerTexto::salvarSaida(string saida, string nome) {
	fstream arquivo;
	arquivo.open(nome, std::fstream::out | std::fstream::app);
	if (arquivo.is_open()) {
		arquivo << saida;
		arquivo << "\n";

	}
}