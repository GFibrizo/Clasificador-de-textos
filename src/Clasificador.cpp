
/*
 * Clasificador.cpp
 *
 *  Created on: 26/11/2013
 *      Author: fabri
 */

#include "Clasificador.h"

/**********************************************************************/
/**********************************************************************/


Clasificador::Clasificador(vector<Cluster*> clusters, hash hashPrincipal,bool multiPertenencia){
	
	this->PreProcesador =  new PreProcesarDatos(hashPrincipal);
	this->clusters = clusters;
	this->multiPertenencia=multiPertenencia;
}

/**********************************************************************/
/**********************************************************************/


void Clasificador::clasificarNuevoPunto(string ruta, int tamVectorArchivos){
	cout<<"clasif nuevo punto"<<endl;
	Punto nuevoPunto = this->PreProcesador->procesarNuevoDocumento(ruta, tamVectorArchivos); 

	cout<<endl<<"DEBUG"<<endl;
	for (unsigned int x = 0; x < nuevoPunto.vectorDeFrecuencias().size(); x++){
		cout<<nuevoPunto.vectorDeFrecuencias()[x]<<" , ";
	}
	cout<< endl;
	cout<<"pedi el punto"<<endl;
	vector<Cluster*> temps = this->getClustersDistanciaMinima(nuevoPunto);
	cout<<"cacule distancia minima"<<endl;
	for (unsigned int k = 0; k < temps.size(); k++) {
		cout<<"FOR CLASIFICADOR 41: "<<endl;
		temps[k]->agregarElementoSinCalcularCentroide(nuevoPunto); //arreglar?
		}
	cout<<"agregue el punto"<<endl;

}

/**********************************************************************/
/**********************************************************************/


void Clasificador::mostrarPunto(Punto punto){

	for (unsigned int i = 0; i < punto.vectorDeFrecuencias().size(); i++) {
		cout<<punto.vectorDeFrecuencias()[i]<<",";
	}
	cout<<endl;
}

/**********************************************************************/
/**********************************************************************/


vector<Cluster*> Clasificador::getClustersDistanciaMinima(Punto punto) {

	vector<Cluster*> temps;
	double distancia = 0.0;
	double distanciaMin = 0.0;

	// Calculo la distancia de este punto contra cada centroide
	for (unsigned int i = 0; i < this->clusters.size(); i++) {
		distancia = punto.distanciaCoseno(this->clusters[i]->getCentroide());
		cout<<"distancia getClusterDistanciaMinima calisifacdor 67: "<<distancia<<endl;

		if ((distancia == distanciaMin) && (this->multiPertenencia)) {
			temps.push_back(this->clusters[i]);
		}
		/* Si la distancia es minima y nueva-> limpio el vector de clusters,la seteo como distancia minima y agrego este cluster como
		cercano */
		if (distancia >= distanciaMin) {
			temps.clear();
			distanciaMin = distancia;
			temps.push_back(this->clusters[i]);
		}
	}
	return temps;
}
/**********************************************************************/
/**********************************************************************/


// Destructor de la clase Clasificador
Clasificador::~Clasificador() {
	delete this->PreProcesador;
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
