/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include "Tweet.h"

// Construtor sobrecarregado para poder utilizar dois tipos de inicialização
Tweet::Tweet()
{
}
//Construtor Padrao
Tweet::Tweet(int uid, long long int tid, string tw, string da)
{
	userID = uid;
	tweetID = tid;
	tweetText = tw;
	date = da;
}
//Funcao que adiciona um tweet
void Tweet::addTweet(int uid, int tid, string tw, string da)
{
	userID = uid;
	tweetID = tid;
	tweetText = tw;
	date = da;
}
//Retorna o User de um objeto
int Tweet::getUserID()
{
	return userID;
}
//Atribui um UserID a um objeto
void Tweet::setUserID(int uid) {
	userID = uid;
}
//Retorna o TweetID de um objeto
long long int Tweet::getTweetID()
{
	return tweetID;
}
//Atribui um TweetID a um objeto
void Tweet::setTweetID(long long int tid) {
	tweetID = tid;
}
//Retorna o Texto do Tweet de um objeto
string Tweet::getTweetText()
{
	return tweetText;
}
//Atribui um Texto do Tweet a um objeto
void Tweet::setTweetText(string tw) {
	tweetText = tw;
}
//Retorna a data do tweet de um objeto
string Tweet::getDate()
{
	return date;
}
//Atribui uma data do tweet a um objeto
void Tweet::setDate(string da) {
	date = da;
}
//Imprime Tweet em tela
void Tweet::printTweet() {
	cout << userID << " " << tweetID << " " << tweetText << " " << date << endl << "\n";
}
//Destrutor
Tweet::~Tweet() {}