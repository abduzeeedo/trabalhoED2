#include "tweets.h"
#include <string>
#include <stdlib.h>

tweets::tweets(int uid, int tid, const std::string& tw, const std::string& da)
{
    userID = uid;
    tweetID = tid;
    tweet = tw;
    date = da;
}

void tweets::addTweet(int uid, int tid, const std::string& tw, const std::string& da)
{
    userID = uid;
    tweetID = tid;
    tweet = tw;
    date = da;
}

int tweets::getuserID()
{
    return userID;
}

int tweets::gettweetID()
{
    return tweetID;
}

std::string tweets::getTweet()
{
    return tweet;
}

std::string tweets::getDate()
{
    return date;
}

tweets::~tweets(){}
