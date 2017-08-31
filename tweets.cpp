#include "tweets.h"
#include <string>
#include <stdlib.h>
using namespace std;

tweets::tweets(int uid, int tid, char tw, char da)
{
    userID = uid;
    tweetID = tid;
    tweet = tw;
    date = da;
}
int tweets::getUserID()
{
    return userID;
}

int tweets::getTweetID()
{
    return tweetID;
}

char* tweets::getTweet()
{
    return tweet;
}

char* tweets::getDate()
{
    return date;
}

tweets::~tweets(){}
