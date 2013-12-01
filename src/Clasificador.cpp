
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


void Clasificador::clasificarNuevoPunto(string ruta){
	//unsigned int i;
	cout<<"clasif nuevo punto"<<endl;
	Punto nuevoPunto = this->PreProcesador->procesarNuevoDocumento(ruta); 
	vector<float> v = nuevoPunto.vectorDeFrecuencias();
	cout<<"vector de frecuencias del nuevo punto: ";
	for (i = 0; i< v.size();i++){
		cout<<v[i]<<" , ";
			
	}	
	cout<<endl;
//<<<<<<< .mine
	cout<<"luego de pasar ruta"<<endl;
	vector<Punto> centroides;
	
	for (i = 0; i < clusters.size(); i++) {
		centroides.push_back(clusters[i]->getCentroide());
		
		cout<<(clusters[i]->getCentroide()).getDocumento()<<" , "<<endl;//vectorDeFrecuencias)[0];
	}
	cout<<endl<<"VERIFICAR FRECUENCIAS: size clusters: "<<clusters.size()<<endl;
	for (i = 0; i < clusters.size(); i++) {
		for (int j = 0; j < clusters[i]->getCentroide().vectorDeFrecuencias().size() ; j++){
			cout<<clusters[i]->getCentroide().vectorDeFrecuencias()[j]<<" , ";
		}
		cout<<endl;	
	}	
	cout<<"luego del for"<<endl;
	Punto centroideCercano = nuevoPunto.calcularCercanos(centroides);
	i = 0;
	cout<<"antes del while"<<endl;
	while ((CompararCentroides(centroideCercano, centroides[i]) == false) && ( i < centroides.size() )) i++;
//=======
	cout<<"pedi el punto"<<endl;
	vector<Cluster*> temps = this->getClustersDistanciaMinima(nuevoPunto);
	cout<<"cacule distancia minima"<<endl;
	for (unsigned int k = 0; k < temps.size(); k++) {
		temps[k]->agregarElemento(nuevoPunto);
		}
	cout<<"agregue el punto"<<endl;
//>>>>>>> .r151

}

void Clasificador::mostrarPunto(Punto punto){

	for (unsigned int i = 0; i < punto.vectorDeFrecuencias().size(); i++) {
		cout<<punto.vectorDeFrecuencias()[i]<<",";
	}
	cout<<endl;
}
vector<Cluster*> Clasificador::getClustersDistanciaMinima(Punto punto) {

	vector<Cluster*> temps;
	double distancia = 0.0;
	double distanciaMin = 0.0;
	cout<<"Muestro punto "<<endl;
	mostrarPunto(punto);
	cout<<"Muestro centroides "<<endl;
	//Calculo la distancia de este punto contra cada centroide
	for (unsigned int i = 0; i < this->clusters.size(); i++) {
		mostrarPunto(clusters[i]->getCentroide());
//		distancia = punto.distanciaCoseno(this->clusters[i]->getCentroide());
//		cout<<"distancia "<<distancia<<endl;
//
//		if ((distancia == distanciaMin) && (this->multiPertenencia)) {
//			temps.push_back(this->clusters[i]);
//		}
//		//Si la distancia es minima y nueva-> limpio el vector de clusters,la seteo como distancia minima y agrego este cluster como cercano
//		if (distancia >= distanciaMin) {
//			temps.clear();
//			distanciaMin = distancia;
//			temps.push_back(this->clusters[i]);
//			//cout<<"el punto  "<<punto.getNombreDoc()<<" deberia estar en el cluster "<<this->clusters[i]->getCentroide().getNombreDoc()<<endl;
//
//		}

	}

	return temps;
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
