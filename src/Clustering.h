
#ifndef CLUSTERING_H_
#define CLUSTERING_H_
#include <stdbool.h>
#include <chrono>
#include <vector>
#include "Punto.h"
#include "Cluster.h"
#include "ManejadorArchivos.h"
#include "KMeans.h"
#include "Arista.h"

#define DIR_FILE_CLUSTERS "sistema/file_clusters"

using namespace std;

class Clustering {
private:
	vector<Cluster*> lista_de_clusters;
	vector<Punto> semillas;
	vector<Punto> puntos_muestra;
	bool multiPertenencia;
	ManejadorArchivos* manejador;
public:
	//constructor vacio para persistencia
	Clustering();
	//constructor para realizar proceso de clustering
	Clustering(unsigned int cantidad_de_semillas, unsigned int cantidad_docs_total, int tam_muestra, bool multiPertenencia, vector<string> vectorArchivos );
	void Clasificar(Punto nuevo_punto);
	vector<Cluster*> getListaClusters();
	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
	* tomaron como muestra para hacer el clutering*/
	vector<int> obtener_muestra(int cantidad_de_puntos, int cantidad_docs);
	/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
	* agarraron de manera aleatoria de la muestra tomada para agrupar con el clustering jerarquico aglomerativo  */
	vector<int> obtener_puntos_random(int cantidad_de_semillas, vector<int> docs_muestra);
	// recibe una cantidad de docs, una cantidad de semillas, y un vector con sqrt(N.K) 
	// instancias de la clase Punto. Devuelve un vector con K semillas de tipo Punto.
	vector<Punto> buckShot (unsigned int cantSemillas, vector<Punto> lista_puntos);
	vector<int> indices_no_muestreados(int cantidad_docs_total, vector<int> indices_muestra);
	void persistirClusters();
	void levantarClusters();
	bool getMultiPertenencia();



	
};


#endif /* CLUSTERING_H_ */
