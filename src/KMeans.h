/*
 * KMeans.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef KMEANS_H_
#define KMEANS_H_
using namespace std;
#include "Punto.h"
class KMeans {
private:
	int numClusters;
	vector<Punto> puntos;
public:
	KMeans();
	virtual ~KMeans();
};

#endif /* KMEANS_H_ */
