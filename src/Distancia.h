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
#include "Punto.h"


using namespace std;

class Distancia {
	
private:
	
	double distanciaCoseno(Punto punto1, Punto punto2);
   

public:

	//Constructor
	Distancia();
	//Destructor
	~Distancia();

	Punto calcular_mas_cercano(Punto v1, vector<Punto> lista_de_puntos);
  
  
};
#endif /* DISTANCIA_H_ */
