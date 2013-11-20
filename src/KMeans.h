/*
 * KMeans.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef KMEANS_H_
#define KMEANS_H_

using namespace std;
#include "Cluster.h"
#include "Punto.h"
#define MAX_ITERACIONES 5 //TODO VER
#define CANT_CLUSTERS_DEFAULT 3 //TODO VER
class KMeans {
private:
	int numClusters;
	//TODO es necesario tener esto, ya teniendo la lista de clusters donde cada cluster
	//tiene su centroide no estariamos teniendo una lista de centroides?
	vector<Punto> centroides;
	vector<Cluster> clusters;
	int maxIteraciones;
	void calcularCentroides();
	void actualizarCluster();

public:
	KMeans(vector<Punto> puntos,unsigned int maxIteraciones,unsigned int numClusters);
	virtual ~KMeans();
	void calcularClusters();
	void agregarElemento(Punto elemento);
	vector<Cluster> getClusters();
};

#endif /* KMEANS_H_ */

