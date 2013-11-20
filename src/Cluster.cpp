/*
 * Cluster.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Cluster.h"
using namespace std;

Cluster::Cluster() {
	this->centroide= new Punto();
}

Cluster::~Cluster() {
	delete this->centroide;
}

void Cluster::agregarElemento(Punto* elemento){
	//agrego un elemento nuevo
	this->puntos.push_back(elemento);
	//Cuando agrego un elemento recalculo el centroide
	this->calcularCentroide();
}
Punto* Cluster::getCentroide(){
	return this->centroide;
}
bool Cluster::esSimilar(Cluster cluster){
	return true;
}
double Cluster::gradoCohesion(){
	return 0;
}

// Se calcula como el promedio de los puntos que tiene el cluster.
void Cluster::calcularCentroide(){
	Punto* temp= new Punto();
	unsigned int cantPuntos = this->puntos.size();
	//Acumulo en un punto temporal la suma de todas las componentes de los
	//puntos de cluster. Divido cada termino por el total de puntos para normalizar.
	for (unsigned int i = 0;  i < cantPuntos; i++) {
		for (unsigned int j = 0;  j < this->puntos[i]->vectorDeFrecuencias().size(); j++) {
			temp->vectorDeFrecuencias()[j] += (this->puntos[i]->vectorDeFrecuencias()[j])/cantPuntos;
		}
	}
	this->centroide = temp;
}

vector<Punto*> Cluster::getPuntos(){
	return this->puntos;
}
