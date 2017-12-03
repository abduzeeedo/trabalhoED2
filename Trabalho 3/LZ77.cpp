#include "LZ77.h"

LZ77::LZ77(int tamDic, int tamBuffer)
{
    this->tamDic = tamDic;
    this->tamBuffer = tamBuffer;
}
LZ77::~LZ77()
{

}
vector<Tupla*> LZ77::comprimirPalavra(string palavra)
{
    char buffer[tamBuffer];
    char dicionario[tamDic];
    for(int k = 0; k<tamBuffer; k++)
        buffer[k] = '\0';
    for(int k = 0; k<tamDic; k++)
        dicionario[k] = '\0';
    char literal;
    int i = 0;
    int begin_window;
    int index = 0;
    string output;
    vector<Tupla*> tuplas;
    while(i < palavra.size())
    {
        begin_window = i-tamDic;
        if(begin_window<0)
        {
            begin_window = 0;
        }
        for(int j = 0; j<tamDic; j++)
        {
            if(i>=tamDic)
            {
                begin_window = i-tamDic;
                dicionario[j] = palavra[j+begin_window];
            }
            else
            {
                if(j>=i)
                    break;
                else
                    dicionario[j] = palavra[j];
            }

        }
        for(int j = 0; j<(tamBuffer); j++)
            buffer[j] = palavra[i+j];
        Tupla* t = new Tupla();
        t->setP(0);
        t->setL(0);
        t->setC(palavra[i]);
        string strDic(dicionario);
        string strBuffer(buffer);
        cout << "Dic: " << strDic << " |Buffer: " << strBuffer << endl;
        for(int j = tamBuffer-1; j>0; j--)
        {

            string strBuffer2(buffer, j);
            index = strDic.rfind(strBuffer2);
            cout << index << endl;
            if(index >= 0)
            {
                literal = '\0';
                if(i+j < palavra.size())
                {
                    literal = palavra[i+j];
                }
                t->setP(strDic.size() - index - 1);
                t->setL(j);
                t->setC(literal);
                break;
            }
        }
        i = i + t->getL() +1;
        tuplas.push_back(t);
    }

    for(int k = 0; k<tuplas.size(); k++)
    {
        cout <<"(" << tuplas[k]->getP() << ", "<< tuplas[k]->getL() << ", " << tuplas[k]->getC() << ")" << endl;;
    }
    return tuplas;
}

string LZ77::descomprimirPalavra(vector<Tupla*> tuplas)
{
    string output;
    int pos;
    for(int i = 0; i<tuplas.size(); i++)
    {
        pos = output.size() - tuplas[i]->getP() -1;
        for(int j = pos; j<pos+tuplas[i]->getL(); j++)
            output+=(output[j]);
        output+=(tuplas[i]->getC());

    }
     cout << output << endl;
    return output;
}
