#include "HashEncad.h"

long long int comp = 0;
HashEncad::HashEncad(int tam)
{
    m =tam+4;
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
            delete tabela;
        }
    }
}
int HashEncad::funcaoH2(int chave)
{
    return chave % (2*m);
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
        //cout << chave << ": " << posicao << endl;

        if (tabela[posicao].verificaVazio())
        {
            comp++;
            return posicao;
            break;
        }
        else
        {
            comp++;
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
            comp++;
            return posicao;
            break;
        }

        else
        {
            comp++;
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
        comp++;
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
        comp++;
        tabela[posicao].addNo(chave);
    }
}

void HashEncad::inserir(int chave, int tratColis)
{
    int posicao = divisao(chave);
    cout << comp << " C: " << chave << endl;
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
void HashEncad::salvarArquivo(string nome){
    string texto = "comp: " + to_string(comp) + "\n";
    GerTexto* ger = new GerTexto();
    ger->salvarSaida(texto, nome);
    texto = "tamanho da tabela: " + to_string((float)sizeof(tabela) * 0.001) + " KBytes\n";
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
