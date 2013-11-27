/*
 * Clasificador.h
 *
 *  Created on: 26/11/2013
 *      Author: fabri
 *      #include <cstdbool>
 */

#ifndef CLASIFICADOR_H_
#define CLASIFICADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "ManejadorArchivos.h"
#include "VerificadorStopWords.h"
#include "LectorDirectorios.h"
#include "Porter.h"


using namespace std;


class Clasificador{


private:

	PreProcesarDatos* PreProcesador;
	vector<Clusters> clusters;


public:

	void clasificarNuevoPunto(vector<Punto> vectorDocumento);
	virtual ~Clasificador();

};















#endif /* CLASIFICADOR_H_ */
