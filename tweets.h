#ifndef TWEETS_H
#define TWEETS_H
#include <string>


class tweets
{
    private:
        int userID;
        int tweetID;
        char* tweet[];
        char* date[];
    public:
        tweets(int uid, int tid, char tw, char da);
        int getuserID();
        int gettweetID();
        std::string getTweet();
        std::string getDate();
        virtual ~tweets();
};

#endif // TWEETS_H
