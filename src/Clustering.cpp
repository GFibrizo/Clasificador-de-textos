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
	//this->puntos = VECTOR DE PUNTOS DE TODOS LOS DOCUMENTOS
	KMeans* KMeans = new KMeans(this->puntos_docs,MAX_ITERACIONES, 0 ,this->semillas); //numero de clusters??
	Kmeans.calcularClusters();
	this->lista_de_clusters = KMeans.getClusters();
	
}
