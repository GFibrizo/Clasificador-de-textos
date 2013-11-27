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
#include "PreProcesarDatos.h"
#include "Cluster.h"

using namespace std;


class Clasificador{


private:

	PreProcesarDatos* PreProcesador;
	vector<Cluster*> clusters;
	typedef map<string,int> hash;
	bool CompararCentroides(Punto p1, Punto p2);
public:
	Clasificador(vector<Cluster*> clusters, hash hashPrincipal);
	void clasificarNuevoPunto(string ruta);
	virtual ~Clasificador();
	
};















#endif /* CLASIFICADOR_H_ */
