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
int Hashing::divisao(int chave){
    return chave%m;
}
int Hashing::enlacamento(int chave){
    string str = to_string(chave);
    int enlacamento = 0;
    for(int i = 0; i<str.length(); i++){
        enlacamento+=atoi(str.substr(i, i+1).c_str());
    }
    return enlacamento%m;
}
int Hashing::sondLinear(int chave){
}
int Hashing::sondQuadratica(int chave){

}
int Hashing::duploHash(int chave){

}
int Hashing::encadSeparado(int chave){

}
int Hashing::encadCol(int chave){

}
void Hashing::addVetor(int chave, int hashingFunc, int tratColis)
{
        int posicao = 0.0;
        if(hashingFunc == 1)
            posicao = divisao(chave);
        else if(hashingFunc == 2)
            posicao = enlacamento(chave);
        if(table[posicao]==INF)
            table[posicao] = chave;
        else{
            switch(tratColis){
                case 1:
                posicao = sondLinear(chave);
                break;
                case 2:
                posicao = sondQuadratica(chave);
                break;
                case 3:
                posicao = duploHash(chave);
                break;
                case 4:
                posicao = encadSeparado();
                break;
                case 5:
                posicao = encadCol(chave);
                break;
                default:
                break;
                table[posicao] = chave;
            }
        }
}

Hashing::~Hashing()
{
    delete[] table;
}
