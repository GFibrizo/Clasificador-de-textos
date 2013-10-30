/*
 * main.cpp
 *
 *  Created on: 25/10/2013
 *      Author: agu
 */




#include <iostream>
#include <string>
#include "src/ManejadorArchivos.h"
#include "src/VerificadorStopWords.h"
#include "src/Normalizador.h"
using namespace std;


int main (int argc, char **argv) {
//	VerificadorStopWords* verifStopWords= new VerificadorStopWords("files/file2");
//	string palabra;
//	cout<<"Ingrese una palabra para verificar si es un stop"<<endl;
//	 getline (cin,palabra);
//	 if(verifStopWords->verificarPalabra(palabra)){
//		 cout<<"es stopword"<<endl;
//	 }
	Normalizador* normalizador= new Normalizador();
	ManejadorArchivos archivo;
	archivo.abrirLectura("files/file1.txt");
	string lineaaux;
	while(archivo.leerunalinea(lineaaux)){
		cout<<normalizador->normalizarString(lineaaux)<<endl;
	}

	return 0;
}

