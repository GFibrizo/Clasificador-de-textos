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
#include "Distancia.h"
class KMeans {
private:
	int numClusters;
	vector<Punto> centroides;
	vector<Cluster> clusters;
	int maxIteraciones;
	void calcularCentroides();
	void actualizarCluster();

public:
	KMeans(vector<Punto>,int maxIteraciones,int numClusters);
	virtual ~KMeans();
	vector<Cluster> calcularClusters();
	void agregarElemento(Punto elemento);

};

#endif /* KMEANS_H_ */
