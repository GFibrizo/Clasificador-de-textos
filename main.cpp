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
	preDatos->preProcesarDatos();

	return 0;
}

