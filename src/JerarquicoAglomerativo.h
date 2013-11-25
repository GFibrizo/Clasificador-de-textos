#ifndef	JERARQUICOAGLOMERATIVO_H_
#define JERARQUICOAGLOMERATIVO_H_

#include <string.h>
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include "Punto.h"


using namespace std;

class JerarquicoAglomerativo{
public:
	//constructor:
	JerarquicoAglomerativo();
	//destructor:
	virtual ~JerarquicoAglomerativo();
	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
	* tomaron como muestra para hacer el clutering*/
	vector<int> obtener_muestra(int cantidad_de_puntos, int cantidad_docs);
	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
	* agarraron de manera aleatoria de la muestra tomada para agrupar con el clustering jerarquico aglomerativo  */
	vector<int> obtener_puntos_random(int cantidad_de_semillas, vector<int> docs_muestra);
	// recibe una cantidad de docs, una cantidad de semillas, y un vector con sqrt(N.K) 
	// instancias de la clase Punto. Devuelve un vector con K semillas de tipo Punto.
	vector<Punto> buckShot (unsigned int cantSemillas, vector<Punto> lista_puntos);
};

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
	Arista buscar_minimo(vector<Arista> lista_aristas);
	//buscar promedio entre los dos vectores que posee la arista:
	Punto buscar_promedio();
};



#endif /* LECTORDIRECTORIOS_H_ */
