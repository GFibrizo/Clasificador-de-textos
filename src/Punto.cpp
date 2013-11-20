/*
 * Punto.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Punto.h"

Punto::Punto(vector<double> frecPond,int doc) {

	this->frecPond = frecPond;
	this->doc=doc;
}
Punto::Punto(){

}

Punto::~Punto() {
	// TODO Auto-generated destructor stub
}

double Punto::getNorma(){
	double acum=0;


	for (unsigned int i = 0; i < this->frecPond.size(); i++) {
		acum=this->frecPond[i]*this->frecPond[i];

	}
	return sqrt(acum);
}


double Punto::distanciaCoseno(Punto otroPunto){
	double suma = 0.0;
	double coseno;

	for (unsigned int i=0; i<this->frecPond.size()-1; i++){
		suma += (this->frecPond[i] * otroPunto.frecPond[i]);
	}

	coseno = suma / (this->getNorma() * otroPunto.getNorma() );
	return coseno;
}
// Recibe un vector v1 y una lista de vectores.
// Devuelve el vector de la lista de vectores que este mas cerca de v1.
// No estoy segura de "double* lista_de_vectores "
Punto  Punto::calcularCercanos(vector<Punto>  puntos){
	double distancia_maxima = 0;
	double distancia_coseno;
	Punto vector_mas_cercano;

	for(unsigned int i=0; i<puntos.size();i++){
		distancia_coseno = this->distanciaCoseno(puntos[i]);
		if (distancia_coseno > distancia_maxima){
			distancia_maxima = distancia_coseno;
			vector_mas_cercano = puntos[i];
		}
	}
	return vector_mas_cercano;
}



vector<double> Punto::vectorDeFrecuencias(){
	return this->frecPond;
}	

