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
	Punto centroide;
	vector<Punto> puntos;

public:
	Cluster();
	Cluster(Punto centroide, vector<Punto> puntos);
	virtual ~Cluster();
	void agregarElemento(Punto elemento);
	Punto getCentroide();
	bool esSimilar(Cluster cluster);
	float gradoCohesion();
	vector<Punto> getPuntos();
	void vaciarPuntos();
	void setCentroide(Punto centroide);
	void agregarElementoSinCalcularCentroide(Punto punto);
	void calcularCentroide();
};

#endif /* CLUSTER_H_ */
