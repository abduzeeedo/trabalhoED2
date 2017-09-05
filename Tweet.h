#ifndef TWEET_H
#define TWEET_H

#include <string>
#include <stdlib.h>

using namespace std;

class Tweet
{
    private:
        int userID;
        int tweetID;
        string tweetText;
        string date;
    public:
        Tweet();
        Tweet(int uid, int tid, string tw, string da);
        void addTweet(int uid, int tid, string tw, string da);
        int getUserID();
        int getTweetID();
        string getTweetText();
        string getDate();
        virtual ~Tweet();
};

#endif // TWEETS_H
