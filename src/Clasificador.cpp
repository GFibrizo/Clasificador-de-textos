
/*
 * Clasificador.cpp
 *
 *  Created on: 26/11/2013
 *      Author: fabri
 */

include "Clasificador.h"

/**********************************************************************/
/**********************************************************************/


Clasificador::Clasificador(vector<Cluster> clusters, hash hashPrincipal){
	
	this->PreProcesador =  new PreProcesarDatos(hashPrincipal);
	this->clusters = clusters;

}

/**********************************************************************/
/**********************************************************************/


void Clasificador::clasificarNuevoPunto(string ruta){
	
	Punto nuevoPunto =  this->PreProcesador->procesarNuevoDocumento(ruta); 
	vector<Punto> centroides;
	
	for (int i = 0; i < clusters.size(); i++) 
		centroides[i] = clusters[i].getCentroide();
	
	Punto centroideCercano = nuevoPunto.calcularCercanos(centroides);
	i = 0;
	
	//Puede llegar a fallar porque no esta definido un cmp para Punto
	while (centroideCercano != centroide[i]) i++;
	
	clusters[i].agregarElemento(nuevoPunto);
	
}

/**********************************************************************/
/**********************************************************************/


//Destructor de la clase Clasificador
Clasificador::~Clasificador() {

	delete this->PreProcesarDatos;
	delete this->clusters;
}
