#include "HashPalavra.h"
//patch para a funcao to_string
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}
//retorna o maior primo anterior à um numero
long long int HashPalavra::maiorPrimo(int N)
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

//construtor
HashPalavra::HashPalavra(int tam)
{
    m = maiorPrimo(tam + 100);
    cout << "M:" << m << endl;
    tabela = new ListaPalavra[m];
}

//destrutor
HashPalavra::~HashPalavra()
{
    //falta implementar destrutor
}

//Funcoes de hashing
long long int HashPalavra::funcaoHashing(string chave)
{
    int tamanho = 0;
    for(int i=0;i <chave.size(); i++){
        tamanho+=chave[i];
    }
    tamanho = (chave.size() + tamanho*chave.size());
    return tamanho % m;
}
//tratamento de colisao
void HashPalavra::encadSeparado(Palavra* chave)
{
    long long int posicao = funcaoHashing(chave->getConteudo());
    if (!tabela[posicao].verificaVazio())
    {
        tabela[posicao].addNo(chave);
    }
}

//Inserir uma nova chave na tabela, verifica se a posicao da funcao hashing já está ocupada
void HashPalavra::inserir(Palavra* chave)
{
    long long int posicao = funcaoHashing(chave->getConteudo());
    if (tabela[posicao].verificaVazio())
        tabela[posicao].addNo(chave);
    else
        encadSeparado(chave);
}
//Salva os resultados em um arquivo com o nome passado como parametro
void HashPalavra::salvarArquivo(string nome)
{
    GerTexto *ger = new GerTexto();
    string texto;
    texto = "Encadeamento separado\n";
    texto += "Tamanho da tabela: ";
    texto += to_string(m);
    texto += "\n";
    texto += "tamanho da tabela: ";
    texto += to_string((float)sizeof(tabela) * 0.001);
    texto += " KBytes\n";
    ger->salvarSaida(texto, nome);
    delete ger;
}
//retorna o tweet com id desejado
Palavra* HashPalavra::retornaPorPalavra(string id){
    long long int posicao = funcaoHashing(id);
    if(tabela[posicao].verificaVazio())
        return NULL;
    else {
        return tabela[posicao].retornaPorId(id);
    }
}
//retorna o primeiro tweet da posicao desejada
Palavra* HashPalavra::retornaPorPosicao(int id){
    if(tabela[id].verificaVazio())
        return NULL;
    else {
        tabela[id].inicio();
        return tabela[id].retornaPrimeiro();
    }
}

//Exibe a tabela e seus valores
void HashPalavra::exibirTabela()
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
