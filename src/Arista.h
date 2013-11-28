#ifndef	ARISTA_H_
#define ARISTA_H_

#include <string.h>
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h>
#include <vector>
#include "Punto.h"

/* USO: para guardar dos vectores con su distancia y sus indices de docs correspondientes*/

using namespace std;

class Arista{
private:
	Punto v1;
	Punto v2;
	double distancia;
	int i1; //indice donde se encuentra el punto v1
	int i2;	 //idem v2.
	
public:
	Arista();
	//constructor:
	Arista(Punto v1,Punto v2,double distancia,int i1,int i2);
	//destructor:
	virtual ~Arista();
	double getDistancia();
	Punto getV1();
	Punto getV2();
	int getI1();
	int getI2();
	Arista buscar_minimo(vector<Arista*> lista_aristas);
	//buscar promedio entre los dos vectores que posee la arista:
	Punto buscar_promedio();
};



#endif /* ARISTA_H_ */
