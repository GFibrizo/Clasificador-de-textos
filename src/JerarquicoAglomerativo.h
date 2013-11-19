#ifndef	JERARQUICOAGLOMERATIVO_H_
#define JERARQUICOAGLOMERATIVO_H_

#include <string.h>
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include "Punto.h"
#include "Distancia.h"

using namespace std;

class JerarquicoAglomerativo{
public:
	//constructor:
	JerarquicoAglomerativo();
	//destructor:
	virtual ~JerarquicoAglomerativo();
	// recibe una cantidad de puntos K y una cantidad de docs N y devuelve un vector de 
	// sqrt(N.K) enteros random.
	vector<int> obtener_puntos_random(int cantidad_de_puntos, int cantidad_docs);
	// recibe una cantidad de docs, una cantidad de semillas, y un vector con sqrt(N.K) 
	// instancias de la clase Punto. Devuelve un vector con K semillas de tipo Punto.
	vector<Punto> buckShot (int cantDocs,unsigned int cantSemillas, vector<Punto> lista_puntos);
};

class Arista{
private:
	Punto v1;
	Punto v2;
	double distancia;
	int i1; //indice donde se encuentra el punto v1
	int i2;	 //idem v2.
	Arista buscar_minimo(vector<Arista> lista_aristas);
	Punto buscar_promedio(Arista arista);
	
public:
	Arista();
	//constructor:
	Arista(Punto v1,Punto v2,double distancia,int i1,int i2);
	//destructor:
	virtual ~Arista();
	double dar_distancia();
	Punto dar_v1();
	Punto dar_v2();
	int dar_i1();
	int dar_i2();
};



#endif /* LECTORDIRECTORIOS_H_ */
