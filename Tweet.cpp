#include "Tweet.h"
#include <string>
#include <stdlib.h>
using namespace std;

// Construtor sobrecarregado para poder utilizar dois tipos de inicialização
Tweet::Tweet()
{
}
Tweet::Tweet(int uid, int tid, char tw[], char da[])
{
    userID = uid;
    tweetID = tid;
    tweetText = tw;
    date = da;
}
void Tweet::addTweet(int uid, int tid, char tw[], char da[])
{
    userID = uid;
    tweetID = tid;
    tweetText = tw;
    date = da;
}
int Tweet::getUserID()
{
    return userID;
}

int Tweet::getTweetID()
{
    return tweetID;
}

char *Tweet::getTweetText()
{
    return tweetText;
}

char *Tweet::getDate()
{
    return date;
}

Tweet::~Tweet() {}
