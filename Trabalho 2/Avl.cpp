#include "Avl.h"

Avl::Avl(){
raiz  = NULL;
}
Avl::~Avl(){

}
bool Avl::busca(int chave){
  return buscaAuxiliar(chave, raiz);
}
bool Avl::buscaAuxiliar(int chave, No* no){
  if(no==NULL)
    return false;
  else if(no->chave  == chave)
    return true;
  else if(no->chave != chave){
    if(no->esq != NULL && no->chave < chave)
      return buscaAuxiliar(chave, no->esq);
    else if(no->dir != NULL && no->chave >= chave)
      return buscaAuxiliar(chave, no->dir);
    else if(no->esq == NULL && no->dir == NULL)
      return false;
  }
}
void Avl::inserir(int chave){

}
void Avl::remover(int chave){
  
}
