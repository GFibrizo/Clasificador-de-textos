/*
 * KMeans.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "KMeans.h"
using namespace std;
KMeans::KMeans(vector<Punto> puntos,unsigned int maxIteraciones,unsigned int numClusters,vector<Punto> semillas) {
	//Si no se define un numero de clusters, se usa el por defecto
	if(numClusters==0){
		this->numClusters=CANT_CLUSTERS_DEFAULT;
	}
	if(maxIteraciones==0){
		this->maxIteraciones=MAX_ITERACIONES;
	}
	this->semillas=semillas;
	this->puntos=puntos;
}

KMeans::~KMeans() {
	// TODO Auto-generated destructor stub
}
/*
 * Aca es donde va la magia
 */
void KMeans::calcularClusters(){
	int cantIteraciones=0;
	double distancia,distanciaMin;

	//Primero calculo los centroides de los clusters con las semillas
	inicializarCentroides();
	Cluster temp;
	//dejo de iterar cuando llego al maximo de iteraciones o no se registran cambios en los clusters
	while((cantIteraciones<this->maxIteraciones) || (!this->cambiosClusters())){
		this->actualizarCentroides();
		//itero sobre todos los puntos
		for (unsigned int j = 0; j < this->puntos.size(); j++) {

			distanciaMin=2;
			//Calculo la distancia de este punto contra cada centroide
			for (unsigned int i = 0; i < this->getClusters().size(); i++) {
				distancia=this->puntos[j].distanciaCoseno(*(this->getClusters()[i].getCentroide()));
				if(distancia<distanciaMin){
					distanciaMin=distancia;
					temp= this->getClusters()[i];
				}

			}
			//Una vez obtenido el cluster al cual el punto esta a menor distancia
			//Agrego este punto al cluster y se actualiza su centroide
			temp.agregarElemento(&this->puntos[j]);
		}

		cantIteraciones++;
	}

}

/*
 * Verifica si en la iteracion se realizo un cambio significativo de cada centroide
  */
bool KMeans::cambiosClusters(){
	int cantDiferentes=0;
	double difCentroides;
	Punto oldCentroid,newCentroid;
	for (unsigned int i = 0; i < this->getClusters().size(); i++) {
		oldCentroid=this->centroides[i];
		newCentroid=*(this->getClusters()[i].getCentroide());
		difCentroides=oldCentroid.distanciaCoseno(newCentroid);
		if(difCentroides>= CORRIMIENTO_MINIMO){
			cantDiferentes++;
		}
	}
	//Utilizo el criterio que si menos del 75% de los centroides no variaron, entonces llegue
	//a una convergencia ya que "no tuve cambios"
	if(cantDiferentes<(this->semillas.size()*0,75)) return false;
	return true;
}
/*
 * Guardo los centroides antes de calcular las nuevas distancias
 */
void KMeans::actualizarCentroides(){
	for (unsigned int i = 0; i < this->semillas.size(); i++) {
		this->centroides[i]=*(this->clusters[i].getCentroide());
	}

}
vector<Cluster> KMeans::getClusters(){
	return this->clusters;
}
/*
 * Inicializa los centroides de los clusters con las semillas obtenidas del jerarquico
 */
void KMeans::inicializarCentroides(){
	for (int i = 0; i < this->semillas.size(); ++i) {
		Cluster cluster;
		//Cada vez que agrego el elemento al cluster estoy actualizando su centroide
		//Como en este caso tengo un solo elemento, este es su centroide
		cluster.agregarElemento(&this->semillas[i]);
		this->clusters.push_back(cluster);
		//Agrego a la lista de centroides que luego se usa para verificar cambios
		this->centroides.push_back(this->semillas[i]);
	}
}

/*
 * Debe buscar el centroide mas cercano y agregarlo al cluster correspondiente
 */
void KMeans::agregarElemento(Punto elemento){



}
