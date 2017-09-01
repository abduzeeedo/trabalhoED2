#ifndef GERTEXTO_H
#define GERTEXTO_H

#include <iostream>
#include <string>
#include "tweets.h"
#include <fstream>

using namespace std;

class gerTexto{
private:

public:
    tweets* carregarTweets(string nome);
    gerTexto();
    ~gerTexto();
};
#endif