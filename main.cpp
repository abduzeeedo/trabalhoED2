#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"
#include "tweets.h"

using namespace std;

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
