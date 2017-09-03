#include "Hashing.h"

#define INF -10000
Hashing::Hashing(int tamanho)
{
    //tamanho da tabela
    m = 2 * tamanho;
    table = new int[m];
    for (int i = 0; i < m; i++)
    {
        table[i] = INF;
    }
}
//Funcoes de hashing
int Hashing::divisao(int chave)
{
    return chave % m;
}
int Hashing::enlacamento(int chave)
{
    string str = to_string(chave);
    int enlacamento = 0;
    for (int i = 0; i < str.length(); i++)
    {
        enlacamento += atoi(str.substr(i, i +).c_str());
    }
    return enlacamento % m;
}
void addVetor(int chave, int hashingFunc, int tratColis)
{
    int posicao = 0.0;
    if (hashingFunc == 1)
        posicao = divisao(chave);
    else if (hashingFunc == 2)
        posicao = enlacamento(chave);
    if (table[posicao] == INF)
        table[posicao] = chave;
    else
    {
        switch (tratColis)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
        }
    }
}

Hashing::~Hashing()
{
    delete[] table;
}
