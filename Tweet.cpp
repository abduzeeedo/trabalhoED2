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
void Tweet::setUserID(int uid) {
	userID = uid;
}
int Tweet::getTweetID()
{
	return tweetID;
}
void Tweet::setTweetID(int tid) {
	tweetID = tid;
}
string Tweet::getTweetText()
{
	return tweetText;
}
void Tweet::setTweetText(string tw) {
	tweetText = tw;
}

string Tweet::getDate()
{
	return date;
}
void Tweet::setDate(string da) {
	date = da;
}
void Tweet::printTweet() {
	cout << userID << " " << tweetID << " " << tweetText << " " << date << endl << "\n";
}
Tweet::~Tweet() {}