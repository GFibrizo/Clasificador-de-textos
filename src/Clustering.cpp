/* IDEA GENERAL
 * 1) Se construye instancia de Jerarquico Aglomerativo, y se piden los indices de los puntos randoms con:
 * vector<int> obtener_puntos_random(int cantidad_de_puntos, int cantidad_docs); siendo cantidad_de_puntos = k semillas.
 * 2) Se cargan en memoria los puntos de esos documentos en un vector <Puntos>
 * 3) Se hace el Buckshot con: vector<Punto> buckShot (int cantDocs,unsigned int cantSemillas, vector<Punto> lista_puntos);
 * que devuelve una lista de K puntos semillas.
 * 4) Se hace el K-means: 
 * 4.1) Se crea una instancia: KMeans(vector<Punto> puntos,unsigned int maxIteraciones,unsigned int numClusters,vector<Punto> semillas);
 * 4.2) Se hace el proceso: KMeans::calcularClusters();
 * Ahora se supone que tenemos los clusteres hechos. Los va a tener Clustering? o K-Means?
