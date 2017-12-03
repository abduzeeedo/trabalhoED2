/*---------------------------------------
TRABALHO DE ESTRUTURA DE DADOS 2
GRUPO:
Bruno Carvalho
Diogo Destefano
Rafael Terra
Pedro Bellotti
--------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Tweet.h"
#include "GerTexto.h"
#include "LZ77.h"
#include "Tupla.h"
string saida = "";
using namespace std;

//Funcao usada para pegar as linhas do arquivo do Menu.
//Entrada: Arquivo .txt com os dados do Menu
//Saída: String lida na linha analizada.

int main(){
	LZ77* teste = new LZ77(6,4);
	vector<Tupla*> t;
	t = teste->comprimirPalavra("bananabanabofana");
	cout << teste->descomprimirPalavra(t);
}
