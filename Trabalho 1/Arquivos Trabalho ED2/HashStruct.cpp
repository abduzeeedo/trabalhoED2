/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "HashStruct.h"
//preenche todas as posicoes com -2
HashStruct::HashStruct(int tam)
{
    m = tam + 4;
    comparacoes = 0;
    tabela = new lista[m];
    for (int i = 0; i < m; i++)
    {
        tabela[i].posVazia = true;
        tabela[i].prox = -2;
    }
}
//Funcoes de hahsing
long long int HashStruct::divisao(long long int chave)
{
    return chave % m;
}
long long int HashStruct::enlacamento(long long int chave)
{
    string str = to_string(chave);
    int enlacamento = 0;
    for (int i = 0; i < str.length(); i++)
    {
        enlacamento += atoi(str.substr(i, i + 1).c_str());
    }
    return enlacamento % m;
}
//Tratamento de colisoes
void HashStruct::encadCol(long long int chave)
{
    int posicao = divisao(chave);
    for (int i = m - 1; i >= 0; i--)
    {
        if (tabela[i].posVazia)
        {
            comparacoes++;
            tabela[i].chave = chave;
            tabela[posicao].prox = i;
            tabela[i].prox = -1;
            tabela[i].posVazia = false;
            break;
        }
        else
            comparacoes++;
    }
}
//Inserir uma nova chave na tabela
void HashStruct::inserir(long long int chave)
{
	long long int posicao = 0;
    posicao = divisao(chave);
    if (tabela[posicao].posVazia)
    {
        tabela[posicao].chave = chave;
        tabela[posicao].prox = -1;
        tabela[posicao].posVazia = false;
    }
    else
        encadCol(chave);
}
void HashStruct::exibirTabela()
{
    cout << "Chave : Proximo" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << tabela[i].chave << " : " << tabela[i].prox << endl;
    }
}
//Salva os resultados em um arquivo com o nome passado como parametro
void HashStruct::salvarArquivo(string nome)
{
    GerTexto *ger = new GerTexto();
    string texto;
    texto = "Encadeamento coalescido\n";
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
HashStruct::~HashStruct()
{
    delete tabela;
}
