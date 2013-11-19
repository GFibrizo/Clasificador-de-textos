/*
 * Punto.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef PUNTO_H_
#define PUNTO_H_
#include <vector>
#include<math.h>
using namespace std;

class Punto {
private:
	vector<double> frecPond;
	int doc;

public:
	Punto();
	Punto(vector<double> frecPond,int doc);
	virtual ~Punto();
	double getNorma();


	int getDocumento();
	Punto  calcularCercanos(vector<Punto>  puntos);
	double distanciaCoseno(Punto otroPunto);

	vector<double> vectorDeFrecuencias();

};

#endif /* PUNTO_H_ */
