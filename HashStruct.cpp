#include "HashStruct.h"
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
int HashStruct::divisao(int chave)
{
    return chave % m;
}
int HashStruct::enlacamento(int chave)
{
    string str = to_string(chave);
    int enlacamento = 0;
    for (int i = 0; i < str.length(); i++)
    {
        enlacamento += atoi(str.substr(i, i + 1).c_str());
    }
    return enlacamento % m;
}
void HashStruct::encadCol(int chave)
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
void HashStruct::inserir(int chave)
{
    int posicao = 0;
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
