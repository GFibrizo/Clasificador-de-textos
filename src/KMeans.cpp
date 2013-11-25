/*
 * KMeans.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "KMeans.h"
using namespace std;
KMeans::KMeans(vector<Punto> *puntos, unsigned int maxIteraciones,
		vector<Punto> *semillas) {

	this->numClusters = semillas->size();

	if (maxIteraciones == 0) {
		this->maxIteraciones = MAX_ITERACIONES;
	} else {
		this->maxIteraciones = maxIteraciones;
	}
	this->semillas = *semillas;
	this->puntos = *puntos;
}

KMeans::~KMeans() {
	// TODO Auto-generated destructor stub
}
/*
 * Aca es donde va la magia
 */
void KMeans::calcularClusters() {

	int cantIteraciones = 0;
	//Primero calculo los centroides de los clusters con las semillas
	inicializarCentroides();
	Cluster* temp;
	//imprimirClusters();

	//dejo de iterar cuando llego al maximo de iteraciones y no se registran cambios en los clusters
	while ((cantIteraciones < this->maxIteraciones)
			&& (!this->cambiosClusters())) {
		//cout << "iteracion: " << cantIteraciones << endl;
		this->actualizarCentroides();

		//itero sobre todos los puntos

		for (unsigned int j = 0; j < this->puntos.size(); j++) {
			temp = this->getClusterDistanciaMinima(puntos[j]);
			//Una vez obtenido el cluster al cual el punto esta a menor distancia
			//Agrego este punto al cluster
			temp->agregarElemento(&this->puntos[j]);

		}
		//imprimirClusters();
		cantIteraciones++;
	}

}
void KMeans::imprimirClusters() {

	for (unsigned int i = 0; i < clusters.size(); ++i) {
		cout << "Cluster: " << endl;
		cout << "tamaño del cluster: " << clusters[i].getPuntos().size()
				<< endl;
		for (unsigned int j = 0; j < clusters[i].getPuntos().size(); ++j) {

			cout << clusters[i].getPuntos()[j]->getDocumento() << endl;
		}
	}
}
Cluster* KMeans::getClusterDistanciaMinima(Punto punto) {
	Cluster* temp;
	double distancia = 0;
	double distanciaMin = 2;
	//Calculo la distancia de este punto contra cada centroide
	for (unsigned int i = 0; i < this->clusters.size(); i++) {
		distancia = punto.distanciaCoseno(*(this->clusters[i].getCentroide()));
		if (distancia < distanciaMin) {
			distanciaMin = distancia;
			temp = &this->clusters[i];
		}

	}

	return temp;
}

/*
 * Verifica si en la iteracion se realizo un cambio significativo de cada centroide
 */
bool KMeans::cambiosClusters() {
	int cantDiferentes = 0;
	double difCentroides;
	Punto oldCentroid, newCentroid;
	for (unsigned int i = 0; i < this->getClusters().size(); i++) {
		oldCentroid = this->centroides[i];
		newCentroid = *(this->getClusters()[i].getCentroide());
		difCentroides = oldCentroid.distanciaCoseno(newCentroid);
		if (difCentroides >= CORRIMIENTO_MINIMO) {
			cantDiferentes++;
		}
	}
	//Utilizo el criterio que si menos del 75% de los centroides no variaron, entonces llegue
	//a una convergencia ya que "no tuve cambios"
	if (cantDiferentes < (this->semillas.size() * 0.75)) {
		return false;
	}
	return true;
}
/*
 * Guardo los centroides antes de calcular las nuevas distancias
 */
void KMeans::actualizarCentroides() {
	for (unsigned int i = 0; i < this->semillas.size(); i++) {

		this->centroides[i] = *(this->clusters[i].getCentroide());
		this->clusters[i].vaciarPuntos();
	}

}
vector<Cluster> KMeans::getClusters() {
	return this->clusters;
}
/*
 * Inicializa los centroides de los clusters con las semillas obtenidas del jerarquico
 */
void KMeans::inicializarCentroides() {

	Cluster* cluster;
	for (unsigned int i = 0; i < this->semillas.size(); i++) {
		cluster = new Cluster();
		//Cada vez que agrego el elemento al cluster estoy actualizando su centroide
		//Como en este caso tengo un solo elemento, este es su centroide
		cluster->agregarElemento(&this->semillas[i]);
		this->clusters.push_back(*cluster);
		//Agrego a la lista de centroides que luego se usa para verificar cambios
		this->centroides.push_back(this->semillas[i]);
		delete cluster;
	}

}

/*
 * Debe buscar el centroide mas cercano y agregarlo al cluster correspondiente
 */
void KMeans::agregarElemento(Punto elemento) {

	Cluster* temp = this->getClusterDistanciaMinima(elemento);
	temp->agregarElemento(&elemento);

}
vector<Punto> KMeans::getPuntos() {
	return this->puntos;
}
vector<Punto> KMeans::getSemillas() {
	return this->semillas;
}
vector<Punto> KMeans::getCentroides() {
	return this->centroides;
}
