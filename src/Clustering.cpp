#include "Clustering.h"

/* IDEA GENERAL
 * 1) Se construye instancia de Jerarquico Aglomerativo, y se piden los indices de los puntos randoms con:
 * vector<int> obtener_puntos_random(int cantidad_de_puntos, int cantidad_docs); 
 * siendo cantidad_de_puntos = k semillas.
 * 2) Se cargan en memoria los puntos de esos documentos en un vector <Puntos>
 * 3) Se hace el Buckshot con: 
 * vector<Punto> buckShot (int cantDocs,unsigned int cantSemillas, vector<Punto> lista_puntos);
 * que devuelve una lista de K puntos semillas.
 * 4) Se hace el K-means: 
 * 4.1) Se crea una instancia: 
 * KMeans(vector<Punto> puntos,unsigned int maxIteraciones,unsigned int numClusters,vector<Punto> semillas);
 * 4.2) Se hace el proceso: KMeans::calcularClusters();
 * Ahora se supone que tenemos los clusteres hechos. 
 */


Clustering::Clustering(unsigned int cantidad_de_semillas, unsigned int cantidad_docs_total, int tam_muestra){
	
	JerarquicoAglomerativo* jerarquico = new JerarquicoAglomerativo();
	ManejadorArchivos* manejador = new ManejadorArchivos();
	
	//muestra de M documentos:
	vector<int> indices_muestra = jerarquico->obtener_muestra(tam_muestra, cantidad_docs_total);
	//indices de puntos random
	vector<int> indices_random = jerarquico->obtener_puntos_random(cantidad_de_semillas, indices_muestra);

	//lista de puntos random:
	vector<Punto> puntos_iniciales= manejador->LevantarListaDePuntos(indices_random);
	//lista de puntos muestra:
	this->puntos_muestra = manejador->LevantarListaDePuntos(indices_muestra);
	//obtiene semillas:
	this->semillas = jerarquico->buckShot(cantidad_de_semillas, puntos_iniciales);

	//K-Means:
	KMeans instancia_KMeans = KMeans(this->puntos_muestra, 0 , this->semillas); //MAX_ITERACIONES = 0, DEFINIR.
	(&instancia_KMeans)->calcularClusters();
	this->lista_de_clusters = instancia_KMeans.getClusters();

	//CLASIFICAR LOS DEMAS PUNTOS:
	//creo lista de indices de los puntos que no estan en la muestra
	vector<int> indices_no_muestreados;
	int indice = 0;
	for (unsigned int i = 0; i < cantidad_docs_total; i++){
		unsigned int numero_doc_muestra = indices_muestra[indice];
		if (i != numero_doc_muestra) indices_no_muestreados.push_back(i);
		indice++;
	}		
	//Genero lista de puntos no muestreados:		
	vector<Punto> lista_no_muestreados = manejador->LevantarListaDePuntos(indices_no_muestreados);
	//Clasifico cada uno de esos puntos:
	for (unsigned int j = 0; j < indices_no_muestreados.size(); j++){
		Clustering::Clasificar(this->lista_de_clusters, lista_no_muestreados[j]);
	}
	
	//ya tengo todos los clusters armados.
		
	delete jerarquico;
	delete manejador;
}





/* CLASIFICACION: IDEA GENERAL
 * 1) [FALTA HACER] Cuando se ingresa un nuevo documento, se preprocesa creando su propio hash secundario.
 * Para generar su vector de frecuencias, se buscan las claves del hash principal ya usado para los 
 * demas documentos en el hash secundario de este nuevo documento. Luego se pondera con TFxIDF.
 * Luego se crea el Punto. (*)
 * 
 * 2)Para Clasificarlo: se toma la lista_de_clusters del Clustering y se comparan los centroides de cada cluster
 * con el nuevo punto en busca de la minima distancia. Una vez que se tiene la minima distancia hay que comparar
 * otra vez buscando otros centroides a la misma minima distancia porque si esta en el medio de ambos se agrega
 * a ambos clusters.
 * Una vez que se tiene la lista de clusters donde se debe agregar el nuevo punto, se agrega el punto a cada uno
 * de esos clusters (los centroides se actualizan automaticamente al agregar cada punto).
 */


// (*) UNA VEZ QUE YA TENGO EL NUEVO PUNTO:
// Recibe la lista_de_clusters del Clustering y el nuevo punto ya creado.
void Clustering::Clasificar( vector<Cluster*> lista_de_clusters, Punto nuevo_punto){
	vector<Cluster*> cluster_destino; //lista de los clusters donde se va a agregar el nuevo punto.
	
	// Primero busco cual es la minima distancia.
	double minima_distancia = (*(((*(lista_de_clusters[0])).getCentroide()))).distanciaCoseno(nuevo_punto);
	for (unsigned int i = 1; i < lista_de_clusters.size() ; i++){
		if ( (*(((*(lista_de_clusters[i])).getCentroide()))).distanciaCoseno(nuevo_punto) < minima_distancia){
			minima_distancia = (*(((*(lista_de_clusters[i])).getCentroide()))).distanciaCoseno(nuevo_punto);
		}
	}
	// Despues busco cuales son los clusters que tienen esa minima distancia:
	for (unsigned int j = 0; j < lista_de_clusters.size() ; j++){
		if ( (*(((*(lista_de_clusters[j])).getCentroide()))).distanciaCoseno(nuevo_punto) == minima_distancia){
			cluster_destino.push_back(lista_de_clusters[j]);
		}
	}
	// Agrego el punto a los clusters de la lista:
	for (unsigned int x = 0; x < cluster_destino.size() ; x++){
		(*(cluster_destino[x])).agregarElemento(nuevo_punto); //agregar Clasificacion
	}
	
}
