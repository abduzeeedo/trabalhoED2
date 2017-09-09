#include "HashEncad.h"

HashEncad::HashEncad(int tam, int trat)
{
    tratColis = trat;
    m = tam + 4;
    tabela = new ListaEncad[m];
    comparacoes = 0;
}

HashEncad::~HashEncad()
{
}
int HashEncad::funcaoH2(int chave)
{
    return (chave + 1) % m;
}
int HashEncad::divisao(int chave)
{
    return chave % m;
}
int HashEncad::enlacamento(int chave)
{
    string str = to_string(chave);
    int enlacamento = 0;
    for (int i = 0; i < str.length(); i++)
    {
        enlacamento += atoi(str.substr(i, i + 1).c_str());
    }
    return enlacamento % m;
}
int HashEncad::sondLinear(int chave)
{
    int posicao = 0;
    int i = 0, it = 0;
    int hk;
    hk = divisao(chave);
    posicao = hk;
    while (!tabela[posicao].verificaVazio() || it < 2)
    {
        posicao = (hk + i) % m;
        if (tabela[posicao].verificaVazio())
        {
            comparacoes++;
            return posicao;
            break;
        }
        else
        {
            comparacoes++;
            i++;
            if (i >= m - 1)
            {
                i = 0;
                it++;
            }
        }
    }
    return -1;
}
int HashEncad::sondQuadratica(int chave)
{
    int posicao = 0;
    int i = 0, it = 0;
    int hk;
    hk = divisao(chave);
    posicao = hk;
    while (!tabela[posicao].verificaVazio())
    {
        posicao = (posicao + (i * i)) % m;
        if (tabela[posicao].verificaVazio())
        {
            comparacoes++;
            return posicao;
            break;
        }

        else
        {
            comparacoes++;
            i++;
            if (i >= m)
            {
                i = 0;
                it++;
            }
        }
    }
    return posicao;
}
void HashEncad::duploHash(int chave)
{
    int hk = divisao(chave);
    int posicao = hk;
    int rk = funcaoH2(chave);
    int i = 0;
    while (!tabela[posicao].verificaVazio())
    {
        comparacoes++;
        posicao = (hk + i * rk) % m;
        i++;
    }
    tabela[posicao].addNo(chave);
}
void HashEncad::encadSeparado(int chave)
{
    int posicao = divisao(chave);
    if (!tabela[posicao].verificaVazio())
    {
        comparacoes++;
        tabela[posicao].addNo(chave);
    }
}

void HashEncad::inserir(int chave)
{
    int posicao = divisao(chave);
    if (tabela[posicao].verificaVazio())
    {
        tabela[posicao].addNo(chave);
    }
    else
    {
        switch (tratColis)
        {
        case 1:
            posicao = sondLinear(chave);
            if (posicao != -1)
                tabela[posicao].addNo(chave);
            else
                cout << "Nao há posicao vazia na tabela! " << endl;
            break;
        case 2:
            posicao = sondQuadratica(chave);
            if (posicao != -1)
                tabela[posicao].addNo(chave);
            else
                cout << "Nao há posicao vazia na tabela! " << endl;
            break;
        case 3:
            duploHash(chave);
            break;
        case 4:
            encadSeparado(chave);
            break;
        }
    }
}
void HashEncad::salvarArquivo(string nome)
{
    GerTexto *ger = new GerTexto();
    string texto;
    if (tratColis == 1)
        texto = "Sondagem linear\n";
    else if (tratColis == 2)
        texto = "Sondagem quadratica\n";
    else if (tratColis == 3)
        texto = "Duplo hash\n";
    else if (tratColis == 4)
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
void HashEncad::exibirTabela()
{
    for (int i = 0; i < m; i++)
    {
        // if (!tabela[i].verificaVazio())
        // {
        tabela[i].inicio();
        cout << "Tabela[" << i << "]:";
        while (!tabela[i].verificaNull())
        {
            cout << " -> " << tabela[i].consultaChave();
            tabela[i].proxNo();
        }
        cout << endl;
        // }
    }
}
