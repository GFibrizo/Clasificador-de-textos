/* IDEA GENERAL:
 * Cuando se ingresa un nuevo documento, se preprocesa creando su propio hash secundario.
 * Para generar su vector de frecuencias, se buscan las claves del hash principal ya usado para los 
 * demas documentos en el hash secundario de este nuevo documento. Luego se pondera con TFxIDF.
 * Luego se crea el Punto. (*)
 * Para Clasificarlo: se toma la lista_de_clusters del Clustering y se comparan los centroides de cada cluster
 * con el nuevo punto en busca de la minima distancia. Una vez que se tiene la minima distancia hay que comparar
 * otra vez buscando otros centroides a la misma minima distancia porque si esta en el medio de ambos se agrega
 * a ambos clusters.
 * Una vez que se tiene la lista de clusters donde se debe agregar el nuevo punto, se agrega el punto a cada uno
 * de esos clusters (los centroides se actualizan automaticamente al agregar cada punto).
 */






// (*) UNA VEZ QUE YA TENGO EL NUEVO PUNTO:
// Recibe la lista_de_clusters del Clustering y el nuevo punto ya creado.
void Clasificacion::Clasificar( vector<Cluster> lista_de_clusters, Punto* nuevo_punto){
	vector<Cluster> cluster_destino; //lista de los clusters donde se va a agregar el nuevo punto.
	
	// Primero busco cual es la minima distancia.
	double minima_distancia = (lista_de_clusters[0].getCentroide()).distanciaCoseno(nuevo_punto);
	for (unsigned int i = 1; i < lista_de_clusters.size() ; i++){
		if ( (lista_de_clusters[i].getCentroide()).distanciaCoseno(nuevo_punto) < minima_distancia){
			minima_distancia = (lista_de_clusters[i].getCentroide()).distanciaCoseno(nuevo_punto);
		}
	}
	// Despues busco cuales son los clusters que tienen esa minima distancia:
	for (unsigned int j = 0; j < lista_de_clusters.size() ; j++){
		if ( (lista_de_clusters[j].getCentroide()).distanciaCoseno(nuevo_punto) = minima_distancia){
			cluster_destino.push_back(lista_de_clusters[j]);
		}
	}
	// Agrego el punto a los clusters de la lista:
	for (unsigned int x = 0; x < cluster_destino.size() ; x++){
		cluster_destino[x].agregarElemento(nuevo_punto);
	}
	
}
