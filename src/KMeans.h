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
#include <iostream>
/*#define MAX_ITERACIONES 5
#define CORRIMIENTO_MINIMO 0.8
#define PORCENTAJE_CENTROIDES 0.75*/

class KMeans {
private:
	static unsigned int const MAX_ITERACIONES;
	static double const CORRIMIENTO_MINIMO;
	static unsigned int const PORCENTAJE_CENTROIDES;
	int numClusters;
	int maxIteraciones;
	vector<Punto> semillas;
	vector<Cluster*> clusters;
	vector<Punto>puntos;
	vector<Punto> centroides;
	bool multiPertenencia;
	void actualizarCentroides();
	bool cambiosClusters();
	void inicializarCentroides();
	vector<Cluster*> getClustersDistanciaMinima(Punto punto);
	void imprimirClusters();
	vector<Punto> getPuntos();
	vector<Punto> getSemillas();
	vector<Punto> getCentroides();
	void mostrarPunto(Punto punto);
public:
	KMeans(vector<Punto> puntos,unsigned int maxIteraciones,vector<Punto> semillas,bool multiPertenencia);
	virtual ~KMeans();
	void calcularClusters();
	void agregarElemento(Punto elemento);
	vector<Cluster*> getClusters();

};

#endif /* KMEANS_H_ */
