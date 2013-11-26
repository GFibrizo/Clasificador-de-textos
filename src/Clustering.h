
#ifndef CLUSTERING_H_
#define CLUSTERING_H_
#include <stdbool.h>
#include "Punto.h"
#include "Cluster.h"
#include "JerarquicoAglomerativo.h"
#include "ManejadorArchivos.h"
#include "KMeans.h"


using namespace std;

class Clustering {
private:
	vector<Cluster*> lista_de_clusters;
	vector<Punto> semillas;
	vector<Punto> puntos_muestra;
	bool enMasDeUnCluster;
public:
 
	Clustering(unsigned int cantidad_de_semillas, unsigned int cantidad_docs_total, int tam_muestra, bool enMasDeUnCluster);
	void Clasificar(Punto nuevo_punto);
	vector<Cluster*> getListaClusters();
	
	
};


#endif /* CLUSTERING_H_ */
