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


Clustering::Clustering(int cantidad_de_semillas, int cantidad_docs){
	JerarquicoAglomerativo* Jerarquico = new JerarquicoAglomerativo();
	vector<int> indices_random = Jerarquico.obtener_puntos_random(cantidad_de_semillas, cantidad_docs);
	/*NECESITO FUNCION: vector<Punto> cargarIndicesEnMemoria(vector<int> indices);*/
	vector<Punto> puntos_iniciales = cargarIndicesEnMemoria(indices_random);
	this->semillas = JerarquicoAglomerativo::buckShot(cantidad_docs, cantidad_de_semillas, puntos_iniciales);
	//this->puntos = VECTOR DE PUNTOS DE TODOS LOS DOCUMENTOS O MUESTRA.
	KMeans* KMeans = new KMeans(this->puntos_docs,MAX_ITERACIONES, 0 ,this->semillas); //numero de clusters??
	Kmeans.calcularClusters();
	this->lista_de_clusters = KMeans.getClusters();
	//CLASIFICAR LOS DEMAS PUNTOS
	
}





/* CLASIFICACION: IDEA GENERAL
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
void Clustering::Clasificar( vector<Cluster> lista_de_clusters, Punto* nuevo_punto){
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
