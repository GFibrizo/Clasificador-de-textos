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
		this->puntos.push_back(elemento);

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
	void Cluster::calcularCentroide(){
		Punto* temp= new Punto();
		unsigned int cantPuntos=this->puntos.size();
		//Acumulo en un punto temporal la suma de todas las componentes de los
		//puntos de cluster
		for (unsigned int i = 0;  i < cantPuntos-1; i++) {
			for (unsigned int j = 0;  j < this->puntos[i]->vectorDeFrecuencias().size(); j++) {
				temp->vectorDeFrecuencias()[j]+=this->puntos[i]->vectorDeFrecuencias()[j];
			}
		}
		//Ahora divido por el total de puntos para normalizar
		for (unsigned int i = 0;  i < temp->vectorDeFrecuencias().size(); i++) {
			temp->vectorDeFrecuencias()[i]=temp->vectorDeFrecuencias()[i]/cantPuntos;
		}
		this->centroide=temp;
	}
	vector<Punto*> Cluster::getPuntos(){
		return this->puntos;
	}
