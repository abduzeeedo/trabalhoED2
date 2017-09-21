#include "Palavra.h"

Palavra::Palavra()
{
    //ctor
}

//Construtor sobrecarregado
Palavra::Palavra(string c, int f)
{
    conteudo = c;
    frequencia = f;
}

Palavra::~Palavra()
{
    //dtor
}

string Palavra::getConteudo()
{
    return conteudo;
}

void Palavra::setConteudo(string c)
{
    conteudo = c;
}

int Palavra::getFreq()
{
    return frequencia;
}

void Palavra::setFreq(int f)
{
    frequencia = f;
}

void Palavra::aumentaFreq()
{
    frequencia++;
}

int Palavra::getHash()
{
    return numero_hash;
}

void Palavra::setHash(int h)
{
    numero_hash = h;
}
