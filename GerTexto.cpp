#include "GerTexto.h"

GerTexto::GerTexto(){

}

GerTexto::~GerTexto(){
    
}
Tweet* GerTexto::carregarTweets(string nome){
    string linha, buffer, userId, tweetId, tweet, date;
    int tamanho =0;
    Tweet* conjunto;
    fstream arquivo;
    int indBuffer =0, espacos = 0, num_linhas = 0, indTweets = 0;
    arquivo.open(nome, std::fstream::in);
    if(arquivo.is_open()){
        //obtem o numero de linhas do arquivo
        arquivo.clear();
        while(arquivo.good()){
            num_linhas++;
        }
        conjunto = new Tweet[num_linhas];
        arquivo.clear();
        while(arquivo.good()){
            espacos = 0;
            indBuffer = 0;
            getline(arquivo, linha);
            for(int i=0; i<linha.length();i++){
                if(linha[i]!='\t' && linha[i]!='\n'){
                    buffer[indBuffer] = linha[i];
                    indBuffer++;
                }
                if(linha[i]=='\t'){
                    espacos++;
                    indBuffer = 0;
                    if(espacos==1){
                        userId = buffer;
                    }else if(espacos==2){
                        tweetId = buffer;
                    }else if(espacos==3){
                        tweet = buffer;
                        
                    }
                    buffer.clear();
                    indBuffer= 0;                    
                }else if(linha[i]=='\t'){
                    date = buffer;
                    indBuffer=0;
                    buffer.clear();
                }
                conjunto[indTweets] = Tweet(stoi(userId), stoi(tweetId), tweet, date);
                date.clear();
                userId.clear();
                tweetId.clear();
                tweet.clear();
                indTweets++;

            }
            
        }
    }
    return conjunto;
}