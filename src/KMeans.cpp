/*
 * KMeans.cpp
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#include "KMeans.h"
using namespace std;
KMeans::KMeans(vector<Punto> *puntos, unsigned int maxIteraciones,vector<Punto> *semillas,bool multiPertenencia) {

	this->numClusters = semillas->size();

	if (maxIteraciones == 0) {
		this->maxIteraciones = MAX_ITERACIONES;
	} else {
		this->maxIteraciones = maxIteraciones;
	}
	this->multiPertenencia=multiPertenencia;
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
	//Cluster* temp;
	vector<Cluster> temps;
	//imprimirClusters();

	//dejo de iterar cuando llego al maximo de iteraciones y no se registran cambios en los clusters
	while ((cantIteraciones < this->maxIteraciones)
			&& (!this->cambiosClusters())) {
		cout << "iteracion: " << cantIteraciones << endl;
		this->actualizarCentroides();

		//itero sobre todos los puntos

		for (unsigned int j = 0; j < this->puntos.size(); j++) {
			//temp = this->getClusterDistanciaMinima(puntos[j]);
			temps=this->getClustersDistanciaMinima(puntos[j]);
			//Una vez obtenido el cluster al cual el punto esta a menor distancia
			//Agrego este punto al cluster
			for (unsigned int k = 0; k < temps.size(); ++k) {
				temps[k].agregarElemento(this->puntos[j]);
			}
			//temp->agregarElemento(&this->puntos[j]);

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

			cout << clusters[i].getPuntos()[j].getDocumento() << endl;
		}
	}
}

vector<Cluster> KMeans::getClustersDistanciaMinima(Punto punto) {

	vector<Cluster> temps;
	double distancia = 0;
	double distanciaMin = 2;
	//Calculo la distancia de este punto contra cada centroide
	cout<<"Punto "<<punto.getDocumento()<<endl;

	for (unsigned int i = 0; i < this->clusters.size(); i++) {

		//prueba
//		cout<<"num cluster: "<<i<<endl;
//		cout<<"cantidad de elementos: "<<this->clusters[i].getPuntos().size()<<endl;
//		cout<<"Centroide:"<<endl;
//		for (unsigned int j = 0; j < this->clusters[i].getCentroide()->vectorDeFrecuencias().size(); ++j) {
//			cout<<this->clusters[i].getCentroide()->vectorDeFrecuencias()[j]<<endl;
//		}
		//prueba
		distancia = punto.distanciaCoseno(*this->clusters[i].getCentroide());
		cout<<"Distancia "<<distancia<<endl;
		//Si la distancia es minima y nueva-> limpio el vector de clusters,la seteo como distancia minima y agrego este cluster como cercano
		if (distancia < distanciaMin) {
			temps.clear();
			distanciaMin = distancia;
			cout<<"nueva distancia minima"<<endl;
			temps.push_back(this->clusters[i]);

		}
		//si la distancia es igual a la distancia minima, solo lo agrego a la lista de clusters cercanos
		if((distancia==distanciaMin)&&(this->multiPertenencia)){
			cout<<"distancia minima repetida"<<endl;
			temps.push_back(this->clusters[i]);
		}

	}

	return temps;
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
		cluster->agregarElemento(this->semillas[i]);
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
	vector<Cluster> temp = this->getClustersDistanciaMinima(elemento);
	//Una vez obtenido el cluster al cual el punto esta a menor distancia
			//Agrego este punto al cluster
			for (unsigned int k = 0; k < temp.size(); ++k) {
				temp[k].agregarElemento(elemento);
			}




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
