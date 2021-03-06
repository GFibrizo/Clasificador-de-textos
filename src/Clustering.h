
#ifndef CLUSTERING_H_
#define CLUSTERING_H_
#include <stdbool.h>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "Punto.h"
#include "Cluster.h"
#include "ManejadorArchivos.h"
#include "KMeans.h"
#include "Arista.h"
#include "PreProcesarDatos.h"
#include <time.h>
#include <stdlib.h>
#define DIR_FILE_CLUSTERS "sistema/file_clusters"
#define DIR_FILE_SIZE_ARCHIVOS "sistema/file_size_archivos"

using namespace std;

class Clustering {
private:
	vector<Cluster*> lista_de_clusters;
	vector<Punto> semillas;
	vector<Punto> puntos_muestra;
	bool multiPertenencia;
	ManejadorArchivos* manejador;

public:
	// Constructor vacio para persistencia
	Clustering();
	// Constructor para realizar proceso de clustering
	Clustering(unsigned int cantidad_de_semillas, unsigned int cantidad_docs_total, int tam_muestra, bool multiPertenencia, vector<string> vectorArchivos );
	void Clasificar(Punto nuevo_punto);
	vector<Cluster*> getListaClusters();

	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se
	* tomaron como muestra para hacer el clutering*/
	vector<int> obtener_muestra(int cantidad_de_puntos, int cantidad_docs);

	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se
	* agarraron de manera aleatoria de la muestra tomada para agrupar con el clustering jerarquico aglomerativo  */
	vector<int> obtener_puntos_random(int cantidad_de_semillas, vector<int> docs_muestra);

	/* Recibe una cantidad de docs, una cantidad de semillas, y un vector con sqrt(N.K)
	instancias de la clase Punto. Devuelve un vector con K semillas de tipo Punto. */
	vector<Punto> buckShot (unsigned int cantSemillas, vector<Punto> lista_puntos);
	vector<int> indices_no_muestreados(int cantidad_docs_total, vector<int> indices_muestra);
	void persistirClusters();
	void persistirTamVectorArchivos(int tam);
	void levantarClusters();
	int levantarTamVectorArchivos();
	bool getMultiPertenencia();
	vector<Punto> obtenerSemillas(vector<Punto> puntos_muestra,unsigned int k);
};

#endif /* CLUSTERING_H_ */
