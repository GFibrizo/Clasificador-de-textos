/*
 * Distancia.h
 */

#ifndef DISTANCIA_H_
#define DISTANCIA_H_

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <math.h>
#include <vector>

#define CANT_DOCS 3 //solo de prueba

using namespace std;

class Distancia {
	
private:
	
	double distanciaCoseno(double vector1[CANT_DOCS], double vector2[CANT_DOCS]);
   

public:

	//Constructor
	Distancia();
	//Destructor
	~Distancia();

	double* calcular_mas_cercano(double vector[CANT_DOCS], double* lista_de_vectores[]);
  
  
};
#endif /* DISTANCIA_H_ */
