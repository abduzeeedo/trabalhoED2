#ifndef TWEET_H
#define TWEET_H

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Tweet
{
private:
	int userID;//ID do usuario
	long long int tweetID;//ID do tweet
	string tweetText;//Texto em si do tweet 
	string date;//Data do tweet
public:
	Tweet();//Construtor Sobrecarregado
	Tweet(int uid, long long int tid, string tw, string da);//Construtor Padrao, com todas as variaveis
	void addTweet(int uid, int tid, string tw, string da);//Funcao que atribui dados a um objeto
	int getUserID();//Retorna o ID do usuario de um objeto
	long long int getTweetID();//Retorna o ID do tweet de um objeto
	string getTweetText(); //Retorna o Texto do Tweet de um objeto
	string getDate();//Retorna a Data do Tweet de um objeto
	void setUserID(int uid);//Atribui um ID de usuario a um objeto
	void setTweetID(long long int tid);//Atribui um ID de tweet a um objeto
	void setTweetText(string tw); //Atribui um Texto do Tweet a um objeto
	void setDate(string date);//Atribui a Data do Tweet a um objeto
	void printTweet();//Imprime os dados de um Tweet em tela
	~Tweet();//Destrutor
};

#endif // TWEETS_H