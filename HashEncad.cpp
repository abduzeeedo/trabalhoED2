#include "HashEncad.h"
/*Cria uma tabela com tamanho tam+4 e uma opcao de tratamento de colisoes passada como parametro
trat=
    1: Sondagem Linear
    2: Sondagem Quadratica
    3: Duplo Hash
    4: Encadeamento Separado
*/
long long int HashEncad::maiorPrimo(int N)
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

HashEncad::HashEncad(int tam, int trat)
{
    tratColis = trat;
    m = maiorPrimo(tam + 100);
    cout << "M:" << m << endl;
    tabela = new ListaEncad[m];
    comparacoes = 0;
}

HashEncad::~HashEncad()
{
    //falta implementar destrutor
}

//Funcoes de hashing
long long int HashEncad::funcaoH2(long long int chave)
{
    return (chave*3)%m;
}
long long int HashEncad::divisao(long long int chave)
{
    return chave % m;
}
long long int HashEncad::enlacamento(long long int chave)
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
long long int HashEncad::sondLinear(long long int chave)
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
        }
    }
    return -1;
}
long long int HashEncad::sondQuadratica(long long int chave)
{
    int posicao = 0;
    int i = 0, it = 0;
    long long int hk;
    hk = divisao(chave);
    posicao = hk;
    while (!tabela[posicao].verificaVazio())
    {
        i++;
        comparacoes++;        
        posicao = (hk + (i * i)) % m;
    }
    return posicao;
}
void HashEncad::duploHash(long long int chave)
{
    long long int hk = divisao(chave);
    long long int posicao = hk;
    long long int rk = funcaoH2(chave);
    if(rk==0)
        rk = funcaoH2(chave+1);
    int i = 0;
    while (!tabela[posicao].verificaVazio())
    {
        comparacoes++;
        i++;
        posicao = ((hk + (i * rk)) % m);
        
    }
    tabela[posicao].addNo(chave);
}
void HashEncad::encadSeparado(long long int chave)
{
    long long int posicao = divisao(chave);
    if (!tabela[posicao].verificaVazio())
    {
        comparacoes++;
        tabela[posicao].addNo(chave);
    }
}

//Inserir uma nova chave na tabela, verifica se a posicao da funcao hashing já está ocupada

void HashEncad::inserir(long long int chave)
{
    long long int posicao = divisao(chave);
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
//Salva os resultados em um arquivo com o nome passado como parametro
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

//Exibe a tabela e seus valores
void HashEncad::exibirTabela()
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
