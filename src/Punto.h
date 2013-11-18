/*
 * Punto.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef PUNTO_H_
#define PUNTO_H_
using namespace std;

class Punto {
private:
	vector<double> frecPond;
	int doc;
public:
	Punto(vector<double> frecPond,int doc);
	virtual ~Punto();
};

#endif /* PUNTO_H_ */
