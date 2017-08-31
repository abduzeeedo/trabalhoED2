/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hashing;

import java.util.Random;

/**
 *
 * @author user
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Hashing h = new Hashing();
        Random r = new Random();
        int contador = 0;
        h.inicializaVetor();
        while (contador < 100){
            if (h.enderecamento(r.nextInt(1000))){
                contador++;
            }
        }        
        System.out.println(h.getNumColisoes());        
    }    
}
