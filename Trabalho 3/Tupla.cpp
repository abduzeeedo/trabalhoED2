#include "Tupla.h"

Tupla::Tupla()
{
    //ctor
}

Tupla::~Tupla()
{
    //dtor
}

char Tupla::getC()
{
    return c;
}

int Tupla::getL(){
return l;
}

int Tupla::getP()
{
    return p;
}

void Tupla::setC(char c)
{
    this->c = c;
}

void Tupla::setL(int l)
{
    this->l = l;
}

void Tupla::setP(int p)
{
    this->p = p;
}
