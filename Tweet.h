#ifndef TWEET_H
#define TWEET_H
#include <string>


class Tweet
{
    private:
        int userID;
        int tweetID;
        char* tweetText;
        char* date;
    public:
        Tweet();
        Tweet(int uid, int tid, char tw[], char da[]);
        void addTweet(int uid, int tid, char tw[], char da[]);
        int getUserID();
        int getTweetID();
        char* getTweetText();
        char* getDate();
        virtual ~Tweet();
};

#endif // TWEETS_H
