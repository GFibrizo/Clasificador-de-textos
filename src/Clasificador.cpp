
/*
 * Clasificador.cpp
 *
 *  Created on: 26/11/2013
 *      Author: fabri
 */

#include "Clasificador.h"

/**********************************************************************/
/**********************************************************************/


Clasificador::Clasificador(vector<Cluster*> clusters, hash hashPrincipal){
	cout<<"constructor de clasificador::\n";
	this->PreProcesador =  new PreProcesarDatos(hashPrincipal);
	this->clusters = clusters;

}

/**********************************************************************/
/**********************************************************************/


void Clasificador::clasificarNuevoPunto(string ruta){
	unsigned int i;
	cout<<"clasificar nuevo punto"<<endl;
	Punto nuevoPunto =  this->PreProcesador->procesarNuevoDocumento(ruta); 
	cout<<"luego de pasar ruta"<<endl;
	vector<Punto> centroides;
	
	for (i = 0; i < clusters.size(); i++) 
		centroides[i] = clusters[i]->getCentroide();
	cout<<"luego del for"<<endl;
	Punto centroideCercano = nuevoPunto.calcularCercanos(centroides);
	i = 0;
	cout<<"antes del while"<<endl;
	while ((CompararCentroides(centroideCercano, centroides[i]) == false) && ( i < centroides.size() )) i++;

	clusters[i]->agregarElemento(nuevoPunto);
	cout<<"fin de clasificar nuevo punto"<<endl;
}

/**********************************************************************/
/**********************************************************************/


//Destructor de la clase Clasificador
Clasificador::~Clasificador() {

	delete this->PreProcesador;
	for (unsigned int i = 0 ; i < this->clusters.size() ; i++){
		delete this->clusters[i];
	}	
}

/**********************************************************************/
/**********************************************************************/


bool Clasificador::CompararCentroides(Punto p1, Punto p2){
	
	for (unsigned int i = 0; i < p1.vectorDeFrecuencias().size() ; i++){
		if	(p1.vectorDeFrecuencias()[i] != p2.vectorDeFrecuencias()[i]) return false;
	}	
	
	if (p1.getDocumento() == p2.getDocumento()) return true;
		
	return false;	
	
}
