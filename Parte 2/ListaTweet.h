#ifndef LISTATWEET_H
#define LISTATWEET_H

#include <iostream>
#include "Tweet.h"


class ListaTweet
{

private:
    typedef struct No
    {
        Tweet *atual;
        No *prox;
    } No;
    No *pri;
    No *it;

public:
    ListaTweet();
    ~ListaTweet();
    void addNo(Tweet* tw);
    Tweet *consultaChave();
    Tweet* retornaPrimeiro();
    Tweet *retornaPorId(int id);
    void inicio();
    void proxNo();
    bool verificaUlt();
    bool verificaVazio();
    bool verificaNull();
};
#endif
