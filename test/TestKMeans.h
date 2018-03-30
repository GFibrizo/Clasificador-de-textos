/*
 * TestKMeans.h
 *
 *  Created on: 22/11/2013
 *      Author: agu
 */

#ifndef TESTKMEANS_H_
#define TESTKMEANS_H_
using namespace std;
#include "../src/KMeans.h"
#include "../src/Punto.h"
#include <vector>
#include <cstdlib>
#include <iostream>


class TestKMeans {

private:
	KMeans* kMeans;
	vector<Punto> semillas;
	vector<Punto> puntos;
	static const unsigned int cantPuntos=4;
	static const unsigned int cantSemillas=2;
	void generarSemillas();
	void generarPuntos();
	void generarFrecPond(vector<double> &frecPond,unsigned int i);

public:
	TestKMeans();
	virtual ~TestKMeans();
	vector<Cluster*> getResultadoKMeans();
	vector<Punto> getSemillas();
	vector<Punto> getPuntos();
	unsigned int getCantSemillas();
	unsigned int getCantPuntos();
};

#endif /* TESTKMEANS_H_ */
