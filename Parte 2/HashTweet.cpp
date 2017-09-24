#include "HashTweet.h"
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}
long long int HashTweet::maiorPrimo(int N)
{
    int limite = floor(sqrt(N));
    vector<int> vet(N);
    int tam, num;
    for (num = 2, tam = 0; num <= N; num++, tam++)
        vet[tam] = num;
    int removeu, i = 0;
    while (1)
    {
        removeu = 0;
        if (vet[i] != -1)
            num = vet[i];
        else
        {
            i++;
            continue;
        }
        int j;
        for (j = i + 1; j < tam; j++)
        {
            if (vet[j] % num == 0)
            {
                vet[j] = -1; // remoção do elemento
                removeu = 1;
            }
        }
        if (removeu == 0 || vet[i] == limite)
            break;
        i++;
    }
    for (i = tam - 1; i >= 0; i--)
    {
        if (vet[i] != -1)
        {
            return vet[i];
            break;
        }
    }
}

HashTweet::HashTweet(int tam, int trat)
{
    tratColis = trat;
    m = maiorPrimo(tam + 100);
    cout << "M:" << m << endl;
    tabela = new ListaEncad[m];
    comparacoes = 0;
}

HashTweet::~HashTweet()
{
    //falta implementar destrutor
}

//Funcoes de hashing
long long int HashTweet::divisao(long long int chave)
{
    return chave % m;
}
//tratamento de colisao
void HashTweet::encadSeparado(Tweet* chave)
{
    long long int posicao = divisao(chave->getTweetID());
    if (!tabela[posicao].verificaVazio())
    {
        comparacoes++;
        tabela[posicao].addNo(chave);
    }
}

//Inserir uma nova chave na tabela, verifica se a posicao da funcao hashing já está ocupada
void HashTweet::inserir(Tweet* chave)
{
    long long int posicao = divisao(chave->getTweetID());
    if (tabela[posicao].verificaVazio())
        tabela[posicao].addNo(chave);
    else
        encadSeparado(chave);
}
//Salva os resultados em um arquivo com o nome passado como parametro
void HashTweet::salvarArquivo(string nome)
{
    GerTexto *ger = new GerTexto();
    string texto;
    texto = "Encadeamento separado\n";
    texto += "Tamanho da tabela: ";
    texto += to_string(m);
    texto += "\nComparacoes: ";
    texto += to_string(comparacoes);
    texto += "\n";
    texto += "tamanho da tabela: ";
    texto += to_string((float)sizeof(tabela) * 0.001);
    texto += " KBytes\n";
    ger->salvarSaida(texto, nome);
    delete ger;
}
//retorna o tweet com id desejado
Tweet* HashTweet::retornaPorTweetId(int id){
    long long int posicao = divisao(id);
    if(tabela[posicao].verificaVazio())
        return NULL;
    else {
        return tabela[posicao].retornaPorId(id);
    }
}
//retorna o primeiro tweet da posicao desejada
Tweet* HashTweet::retornaPorPosicao(int id){
    if(tabela[id].verificaVazio())
        return NULL;
    else {
        tabela[id].inicio();
        return tabela[id].retornaPrimeiro();
    }
}

//Exibe a tabela e seus valores
void HashTweet::exibirTabela()
{
    for (int i = 0; i < m; i++)
    {
        tabela[i].inicio();
        cout << "Tabela[" << i << "]:";
        while (!tabela[i].verificaNull())
        {
            cout << " -> " << tabela[i].consultaChave();
            tabela[i].proxNo();
        }
        cout << endl;
    }
}
