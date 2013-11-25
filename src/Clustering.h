
#ifndef CLUSTERING_H_
#define CLUSTERING_H_
#include "Punto.h"
#include "Cluster.h"
#include "JerarquicoAglomerativo.h"
#include "ManejadorArchivos.h"
#include "KMeans.h"
#define MAX_ITERACIONES 10 //(??)

using namespace std;

class Clustering {
private:
	vector<Cluster> lista_de_clusters;
	vector<Punto*> semillas;
	vector<Punto*> puntos_muestra;
public:
	Clustering(unsigned int cantidad_de_semillas, unsigned int cantidad_docs_total, int tam_muestra);
	void Clasificar( vector<Cluster> lista_de_clusters, Punto* nuevo_punto);
	
};


#endif /* CLUSTERING_H_ */
