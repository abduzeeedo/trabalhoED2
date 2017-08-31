#include "gerTexto.h"

gerTexto::gerTexto(){

}

gerTexto::~gerTexto(){
    
}
tweets* gerTexto::carregarTwittes(string nome){
    string linha, buffer;
    tw
    fstream arquivo;
    int j =0, espacos = 0;
    arquivo.open(nome, in);
    arquivo.clear();
    while(arquivo.good()){
        getline(arquivo, linha);
        for(int i=0; i<linha.len();i++){
            if(linha[i]!='\t'){
                buffer[j] = linha[i];
                j++;
            }
            if(linha[i]=='\t'){
                espacos++;
                j = 0;
                if(espacos==1){
                    
                }
                buffer.clear();
            }
        }

    }
}