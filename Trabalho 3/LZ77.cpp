#include "LZ77.h"

LZ77::LZ77()
{
    tamDic = 18;
    tamBuffer = 8;
    buffer = new char[tamBuffer];
    dicionario = new char[tamDic];
}
LZ77::~LZ77()
{
    delete[] buffer;
    delete[] dicionario;
}
string LZ77::comprimirPalavra(string palavra)
{
    vector<Tripla> triplas;
    limpaDicionario();
    LimpaBuffer();
    for(int i = 0; i<palavra.size(); i++)
    {
        if(i==0)
        {
            for(int j = 0; j<tamBuffer; j++) //coloca os caracteres no buffer
                buffer[j] = palavra[j];

        }

    }
}

string LZ77::descomprimirPalavra(string palavra)
{

}
void LZ77::limpaDicionario()
{
    for(int i = 0; i<tamDic; i++)
        dicionario[i] = '\0';
}
void LZ77::LimpaBuffer()
{
    for(int i = 0; i<tamBuffer; i++)
        buffer[i] = '\0';
}
