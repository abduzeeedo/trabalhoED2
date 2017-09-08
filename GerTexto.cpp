#include "GerTexto.h"

GerTexto::GerTexto()
{
}

GerTexto::~GerTexto()
{
}
Tweet *GerTexto::carregarTweet(string nome)
{
    string linha;
    Tweet *tw = new Tweet();
    fstream arquivo;
    arquivo.open(nome, std::fstream::in);
    if(arquivo.is_open()){
        getline(arquivo, linha, '\t');
        tw->setUserID(stoi(linha));
        getline(arquivo, linha, '\t');
        tw->setTweetID(atoi(linha.c_str()));
        getline(arquivo, linha, '\t');
        tw->setTweetText(linha);
        getline(arquivo, linha);
		tw->setDate(linha);
    }
return tw;
}
