/*
 * main.cpp
 *
 *  Created on: 25/10/2013
 *      Author: agu
 */




#include <iostream>
#include <string>
#include "src/PreProcesarDatos.h"


using namespace std;


int main (int argc, char **argv) {

	PreProcesarDatos* preDatos = new PreProcesarDatos("files/");
	/*lee los archivos, arma el hash principal y lo guarda como atributo. Arma los hash secundarios y los guarda en archivos.*/
	preDatos->preProcesarDatos();
	
	//Clustering =  Clustering::Clustering(cantidad_de_semillas, cantidad_docs_total, tam_muestra);
	

	return 0;
}

