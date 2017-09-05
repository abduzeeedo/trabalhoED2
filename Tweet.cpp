#include "Tweet.h"


// Construtor sobrecarregado para poder utilizar dois tipos de inicialização
Tweet::Tweet()
{
}
Tweet::Tweet(int uid, int tid, string tw, string da)
{
    userID = uid;
    tweetID = tid;
    tweetText = tw;
    date = da;
}
void Tweet::addTweet(int uid, int tid, string tw, string da)
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
string Tweet::getTweetText()
{
    return tweetText;
}

string Tweet::getDate()
{
    return date;
}

Tweet::~Tweet() {}
