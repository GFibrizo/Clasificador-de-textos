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
#define CORRIMIENTO_MINIMO 0.8
class KMeans {
private:
	int numClusters;
	int maxIteraciones;
	vector<Punto> semillas;
	vector<Cluster> clusters;
	vector<Punto>puntos;
	vector<Punto> centroides;

	void actualizarCentroides();
	bool cambiosClusters();
	void inicializarCentroides();
	Cluster getClusterDistanciaMinima(Punto punto);
public:
	KMeans(vector<Punto> puntos,unsigned int maxIteraciones,unsigned int numClusters,vector<Punto> semillas);
	virtual ~KMeans();
	void calcularClusters();
	void agregarElemento(Punto elemento);
	vector<Cluster> getClusters();

};

#endif /* KMEANS_H_ */
