/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hashing;

/**
 *
 * @author user
 */
public class Hashing {

    private static final int m = 101;
    private int[] vetor = new int[m];
    private int numColisoes = 0;

    public void inicializaVetor() {
        for (int i = 0; i < m; i++) {
            vetor[i] = -1;
        }
    }

    public int hashingDivisao(int chave) {
        return chave % m;
    }

    public int hashingEnlacamento(int chave) {
        String chaveStr = Integer.toString(chave);
        int enlacamento = 0;
        for (int i = 0; i < chaveStr.length(); i++) {
            enlacamento += Integer.parseInt(chaveStr.substring(i, i + 1));
        }
        return enlacamento % m;
    }

    public boolean adicionaVetor(int chave) {
        //int posicao =  hashingDivisao(chave);
        int posicao = hashingEnlacamento(chave);
        System.out.println("Chave: " + chave + "Posição: " + posicao);
        if (vetor[posicao] == -1) {
            vetor[posicao] = chave;
            return true;
        } else {
            numColisoes++;
            return false;
        }
    }

    public int getNumColisoes() {
        return numColisoes;
    }

    public void tentaProx(int posicao, int chave) {
        numColisoes++;
        posicao++;
        if (vetor[posicao] == -1) {
            vetor[posicao] = chave;
        } else {
            tentaProx(posicao, chave);
        }
    }

    public int sLinear(int posicao){
        return posicao + 1;
    }
    public int sQuadratica(int posicao, int exp){
        posicao = posicao + (exp*exp);
        return posicao;
    }
    public int dupĺoHash(int posicao, int chave){
        posicao = posicao + ((2*chave-1) % m);
        return posicao;
    }
    
    public boolean enderecamento(int chave) {
        int posicao = chave % m;
        int exp = 1;
        int flag = 0;
        System.out.println("Chave: " + chave + "Posição: " + posicao);
        if (vetor[posicao] == -1) {
            vetor[posicao] = chave;
            return true;
        } else {
            while (flag == 0) {
                if (vetor[posicao] == -1) {
                    vetor[posicao] = chave;
                    flag = 1;
                
                } else {
                    numColisoes++;
                    posicao = dupĺoHash(posicao, chave);
                    //exp++;
                    if (posicao >= m){
                        posicao = posicao%m;
                    }
                }
            }
            return true;
        }
    }

}
