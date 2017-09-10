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

//Carrega um vetor de tweets com numTweets tweets, os tweets sao carregados em sequencia
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

void GerTexto::salvarSaida(string saida, string nome){
	fstream arquivo;
	arquivo.open(nome,std::fstream::out | std::fstream::app);
	if(arquivo.is_open()){
		arquivo << saida;
		arquivo << "\n";

	}
}
