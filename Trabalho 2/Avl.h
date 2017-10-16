#ifndef AVL_H
#define AVL_H

using namespace std;

class Avl{
private:
  typedef struct No{
    int chave;
    int fatorBalanceamento;
    No* esq;
    No* dir;
  }No;
  No* raiz;
  bool buscaAuxiliar(int chave, No* no);
public:
  Avl();
  ~Avl();
  void inserir(int chave);
  void remover(int chave);
  bool busca(int chave);

};
#endif
