/*
 * Cluster.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_
#include "Punto.h"
using namespace std;
class Cluster {
private:
	Punto* centroide;
	vector<Punto*> puntos;
	void calcularCentroide();
public:
	Cluster();
	virtual ~Cluster();
	void agregarElemento(Punto* elemento);
	Punto getCentroide();
	bool esSimilar(Cluster cluster);
	float gradoCohesion();
	vector<Punto*> getPuntos();
	void vaciarPuntos();

};

#endif /* CLUSTER_H_ */
