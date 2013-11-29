/*
 * Punto.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Punto.h"

/**********************************************************************/
/**********************************************************************/


Punto::Punto(vector<float> frecPond,int doc) {

	this->frecPond = frecPond;
	this->doc=doc;
	this->nombreDoc = " ";

}

/**********************************************************************/
/**********************************************************************/


Punto::Punto(vector<float> frecPond,int doc, string nombreDoc) {

	this->frecPond = frecPond;
	this->doc=doc;
	this->nombreDoc = nombreDoc;
}

/**********************************************************************/
/**********************************************************************/


Punto::Punto(int doc, string nombreDoc) {

//	this->frecPond = NULL;
	this->doc=doc;
	this->nombreDoc = nombreDoc;
}

/**********************************************************************/
/**********************************************************************/


Punto::Punto(){
	
}

/**********************************************************************/
/**********************************************************************/


Punto::~Punto() {
	// TODO Auto-generated destructor stub
}




float Punto::calcularNorma(){
	float acum=0;

		for (unsigned int i = 0; i < this->frecPond.size(); i++) {
			acum+=pow(this->frecPond[i],2.0);
		}
		return sqrt(acum);
}
/**********************************************************************/
/**********************************************************************/


float Punto::getNorma(){
	return this->norma;
}

/**********************************************************************/
/**********************************************************************/


string Punto::getNombreDoc(){
	return this->nombreDoc;	
}	

/**********************************************************************/
/**********************************************************************/


double Punto::distanciaCoseno(Punto otroPunto){

	double suma =0.0;
	double coseno=0.0;

	for (unsigned int i=0; i<this->frecPond.size(); i++){
		suma=suma+(this->frecPond[i] * otroPunto.frecPond[i]);
	}
	coseno = suma / (this->getNorma() * otroPunto.getNorma() );

	return coseno;
}

/**********************************************************************/
/**********************************************************************/


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

int Punto::getDocumento(){
	return this->doc;
}

/**********************************************************************/
/**********************************************************************/


vector<float> Punto::vectorDeFrecuencias(){
	return this->frecPond;
}	

/**********************************************************************/
/**********************************************************************/


void Punto::setVector(vector<float> vectorDoc){
	
	this->frecPond = vectorDoc;
}
