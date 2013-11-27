#include "Arista.h"


Arista::Arista(){ }

//constructor:
Arista::Arista(Punto v1,Punto v2, double distancia,int i1,int i2){
	this->v1 = v1;
	this->v2 = v2;
	this->distancia = distancia;
	this->i1 = i1;
	this->i2 = i2;	
}

//destructor:
Arista::~Arista(){ }	

double Arista::getDistancia(){
	return this->distancia;
}

Punto Arista::getV1(){
	return this->v1;
}

Punto Arista::getV2(){
	return this->v2;
}

int Arista::getI1(){
	return this->i1;
}

int Arista::getI2(){
	return this->i2;
}

using namespace std;

//busca y devuelve la arista con la minima distancia de una lista de aristas.
Arista* Arista::buscar_minimo(vector<Arista*> lista_aristas){
	double minimo = (*(lista_aristas[0])).getDistancia();
	Arista* menor_arista = lista_aristas[0];
	unsigned int i;
	for (i=1; i < lista_aristas.size(); i++){
		if ((*(lista_aristas[i])).getDistancia() < minimo){
			minimo = (*(lista_aristas[i])).getDistancia();
			menor_arista = lista_aristas[i];
		}
	}
	return menor_arista;	
}

/*Extraigo v1 y v2 de la arista, calculo el vector promedio y creo un nuevo punto que devuelvo.*/
Punto Arista::buscar_promedio(){
	vector<float> v1 = this->getV1().vectorDeFrecuencias();
	vector<float> v2 = this->getV2().vectorDeFrecuencias();
	vector<float> frecPond;
	unsigned int i;
	for (i = 0; i < v1.size(); i++){
		frecPond[i] = (v1[i] + v2[i]) / 2;	
	}
	Punto nuevo_punto = Punto(frecPond, -1);
	return nuevo_punto;
}		



