#ifndef TWEETS_H
#define TWEETS_H
#include <string>


class tweets
{
    private:
        int userID;
        int tweetID;
        std::string tweet;
        std::string date;
    public:
        tweets(int uid, int tid, const std::string& tw, const std::string& data);
        int getuserID();
        int gettweetID();
        std::string getTweet();
        std::string getDate();
        virtual ~tweets();
};

#endif // TWEETS_H
