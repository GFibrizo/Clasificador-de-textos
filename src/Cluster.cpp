/*
 * Cluster.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Cluster.h"
using namespace std;

Cluster::Cluster() {
	this->clustroide= new Punto();


}

Cluster::~Cluster() {
	delete this->clustroide;


}

	void Cluster::agregarElemento(Punto* elemento){
		this->puntos.push_back(elemento);

	}
	Punto* Cluster::getClustroide(){
		return this->clustroide;
	}
	bool Cluster::esSimilar(Cluster cluster){
		return true;
	}
	double Cluster::gradoCohesion(){
		return 0;
	}
	void Cluster::calcularClustroide(){


	}
	vector<Punto*> Cluster::getPuntos(){
		return this->puntos;
	}
