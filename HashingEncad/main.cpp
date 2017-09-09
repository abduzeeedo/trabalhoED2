#include <iostream>
#include "HashEncad.h"
using namespace std;

int main()
{
    HashEncad* hs = new HashEncad(12);
    for(int i = 0; i<24; i++){
        hs->inserir(i, 1);
    }
    hs->exibirTabela();
    //delete hs;
    return 0;
}
