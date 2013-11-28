/*
 * Punto.h
 *
 *  Created on: 18/11/2013
 *      Author: agu
 */

#ifndef PUNTO_H_
#define PUNTO_H_
#include <vector>
#include <string>
#include<math.h>

using namespace std;

class Punto {
private:
	vector<float> frecPond;
	int doc;
	string nombreDoc;

public:
	Punto();
	Punto(vector<float> frecPond,int doc);
	Punto(vector<float> frecPond,int doc, string nombreDoc);
	Punto(int doc, string nombreDoc);
	virtual ~Punto();
	float getNorma();
	int getDocumento();
	Punto  calcularCercanos(vector<Punto>  puntos);
	double distanciaCoseno(Punto otroPunto);
	void setVector(vector<float> vectorDoc);
	string getNombreDoc();
	vector<float> vectorDeFrecuencias();

};

#endif /* PUNTO_H_ */
