/*
 * Cluster.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Cluster.h"
using namespace std;

/**********************************************************************/
/**********************************************************************/


Cluster::Cluster() {
	this->centroide= new Punto();
}

/**********************************************************************/
/**********************************************************************/


Cluster::Cluster(Punto* centroide, vector<Punto*> puntos){
	
	this->centroide = centroide;
	this->puntos = puntos;
	
}

/**********************************************************************/
/**********************************************************************/


Cluster::~Cluster() {
	//TODO
	delete this->centroide;
}

/**********************************************************************/
/**********************************************************************/


void Cluster::agregarElemento(Punto* elemento){
	//agrego un elemento nuevo
	this->puntos.push_back(elemento);
	//Cuando agrego un elemento recalculo el centroide
	this->calcularCentroide();
}

/**********************************************************************/
/**********************************************************************/


Punto Cluster::getCentroide(){
	return *this->centroide;
}

/**********************************************************************/
/**********************************************************************/


bool Cluster::esSimilar(Cluster cluster){
	return true;
}

/**********************************************************************/
/**********************************************************************/


float Cluster::gradoCohesion(){
	//TODO
	return 0;
}

/**********************************************************************/
/**********************************************************************/


// Se calcula como el promedio de los puntos que tiene el cluster.
void Cluster::calcularCentroide(){

	unsigned int cantPuntos = this->puntos.size();

	//obtengo el tamaño que va a tener el vector de frecuencias
	vector<float> frecTemp(this->puntos[0]->vectorDeFrecuencias().size());
	//Acumulo en un punto temporal la suma de todas las componentes de los
	//puntos de cluster. Divido cada termino por el total de puntos para normalizar.
	for (unsigned int i = 0;  i < cantPuntos; i++) {
		for (unsigned int j = 0;  j < this->puntos[i]->vectorDeFrecuencias().size(); j++) {
			frecTemp[j] =frecTemp[j] + (this->puntos[i]->vectorDeFrecuencias()[j])/cantPuntos;
		}
	}
	//Se crea un nuevo punto con el promedio de las frecuencias ponderadas de los puntos del cluster
	//y que tiene como documento al -1 (ya que es un punto que puede ser ficticio)

	Punto* temp= new Punto(frecTemp,-1);
	this->centroide = temp;

}

/**********************************************************************/
/**********************************************************************/


vector<Punto*> Cluster::getPuntos(){
	return this->puntos;
}

/**********************************************************************/
/**********************************************************************/


void Cluster::vaciarPuntos(){
	this->puntos.clear();
}
