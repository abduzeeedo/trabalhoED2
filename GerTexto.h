#ifndef GERTEXTO_H
#define GERTEXTO_H

#include <iostream>
#include <string>
#include "Tweet.h"
#include <fstream>

class GerTexto
{
  private:
  public:
    Tweet* carregarTweets(string nome);
    GerTexto();
    ~GerTexto();
};
#endif