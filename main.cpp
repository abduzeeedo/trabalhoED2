#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"
#include "tweets.h"

using namespace std;
/*
tweets* importarTweets(const char* filename)
{
    string line;
    ifstream myfile(filename); //abre arquivo
    int tam = 10;
    tweets *vetor[tam];

    if (!myfile.is_open())
    {
        cout<<"Problema em abrir o arquivo"<<endl;
    }
    else
    {
        int userid, tweetid, tweet, date;
        while ( true )
        {
            getline (myfile,line);     //pega linha
            if(myfile.eof())           //encontra fim do arquivo
            {
                break;
            }
            else
            {
                for(int i=0;i<tam;i++)
                {
                    sscanf(line.c_str(), "%d %d", &v1, &v2);
                    vetor[i]->addTweet(v1,v2);   //adiciona ao vetor
                }
            }
        }
        myfile.close();
    }
    return vetor;
}
*/

int main()
{
    tweets* vetor[2];
    int id1 = 11;
    int tid1 = 121;
    string t = "teste de tweet1";
    string d = "2017-08-30 16:31:42";

    for (int i=0;i<3;i++)
    {
        vetor[i] = new tweets(id1,tid1,t,d);
    }

    cout<<"ID do usuario: "<<vetor[0]->getuserID()<<endl;
    cout<<"ID do tweet: "<<vetor[0]->gettweetID()<<endl;
    cout<<"Tweet: "<<vetor[0]->getTweet()<<endl;
    cout<<"Data: "<<vetor[0]->getDate()<<endl;
    return 0;
}
