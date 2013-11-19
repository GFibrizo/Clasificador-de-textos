/*
 * Cluster.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_
#include "Punto.h"
#include "Distancia.h"
using namespace std;
class Cluster {
private:
	Punto* clustroide;
	vector<Punto*> puntos;
	void calcularClustroide();
public:
	Cluster();
	virtual ~Cluster();
	void agregarElemento(Punto* elemento);
	Punto* getClustroide();
	bool esSimilar(Cluster cluster);
	double gradoCohesion();
	vector<Punto*> getPuntos();
};

#endif /* CLUSTER_H_ */
