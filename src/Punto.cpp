/*
 * Punto.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "Punto.h"

Punto::Punto(vector<double> frecPond,int doc) {
	this->frecPond=frecPond;
	this->doc=doc;

}
Punto::Punto(){

}

Punto::~Punto() {
	// TODO Auto-generated destructor stub
}

double Punto::getNorma(){
	double acum=0;
	for (int i = 0; i < this->frecPond.size()-1; ++i) {
		acum=this->frecPond[i]*this->frecPond[i];
	}
	return sqrt(acum);
}
