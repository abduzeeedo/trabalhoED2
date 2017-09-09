#include "HashEncad.h"
HashEncad::HashEncad(int tam)
{
    m = 2 * tam;
    cout << "M: " << m << endl;
    tabela = new ListaEncad[m];
    /*  for (int i = 0; i < m; i++)
        tabela[i] = new ListaEncad();
        */
}

HashEncad::~HashEncad()
{
    for (int i = 0; i < m; i++)
    {
        tabela[i].inicio();
        while (!tabela[i].verificaNull())
        {
            delete tabela[i];
        }
    }
}
bool HashEncad::encontrar(int chave, int tratColis)
{
    int hk;
    hk = enlacamento(chave);
    return true;
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
    hk = enlacamento(chave);
    posicao = hk;
    while (!tabela[posicao].verificaVazio() || it < 2)
    {
        posicao = (hk + i) % m;
        //cout << chave << ": " << posicao << endl;

        if (tabela[posicao].verificaVazio())
        {
            return posicao;
            break;
        }
        else
        {
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
    hk = enlacamento(chave);
    posicao = hk;
    while (!tabela[posicao].verificaVazio())
    {
        posicao = (posicao + (i * i)) % m;
        if (tabela[posicao].verificaVazio())
        {
            return posicao;
            break;
        }

        else
        {
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
    int hk = enlacamento(chave);
    int posicao = hk;
    int rk = divisao(chave);
    int i = 0;
    while (!tabela[posicao].verificaVazio() || i < 2 * m)
    {
        posicao = (hk + i * rk) % m;
        i++;
    }
    tabela[posicao].addNo(chave);
}
void HashEncad::encadSeparado(int chave)
{
    int posicao = enlacamento(chave);
    if (!tabela[posicao].verificaVazio())
        tabela[posicao].addNo(chave);
}
void HashEncad::encadCol(int chave)
{
    int posicao = enlacamento(chave);
    for (int i = m - 1; i >= 0; i++)
    {
        if (tabela[i].verificaVazio())
        {
            tabela[i].addNo(chave);
            tabela[posicao].setProxLista(tabela[i]);
        }
    }
}
void HashEncad::inserir(int chave, int tratColis)
{
    int posicao = enlacamento(chave);

    if (tabela[posicao].verificaVazio())
        tabela[posicao].addNo(chave);
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
        case 5:
            encadCol(chave);
            break;
        default:
            break;
        }
    }
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
