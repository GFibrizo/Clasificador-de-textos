/*
 * Clustering.cpp
 *
 *  Created on: 18/11/2013
 *      Author: jas, fabri
 */

#include "Clustering.h"

/**********************************************************************/
/**********************************************************************/

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

Clustering::Clustering() {
}


/**********************************************************************/
/**********************************************************************/

Clustering::Clustering(unsigned int cantidad_de_semillas,
		unsigned int cantidad_docs_total, int tam_muestra,
		bool multiPertenencia, vector<string> vectorArchivos) {

	this->manejador = new ManejadorArchivos();

	this->multiPertenencia =  multiPertenencia;
	//muestra de M documentos:
	vector<int> indices_muestra = this->obtener_muestra(tam_muestra, cantidad_docs_total);
	//indices de puntos random
	vector<int> indices_random = this->obtener_puntos_random(cantidad_de_semillas, indices_muestra);
	
	cout << "\n tam indices muestra:" << indices_muestra.size()
			<< "\n tam indices random: " << indices_random.size() << "\n";
	cout << "indices muestra, indices random  =  " << indices_muestra.size()
			<< "  ;  " << indices_random.size() << endl;
	
	//lista de puntos random:
	vector<Punto> puntos_iniciales = this->manejador->LevantarListaDePuntos(
			indices_random, vectorArchivos);
	//lista de puntos muestra:
	this->puntos_muestra = this->manejador->LevantarListaDePuntos(
			indices_muestra, vectorArchivos);

	cout << "cantidad de puntos muestra desde manejador "
			<< this->puntos_muestra.size() << endl;

	cout << "cantidad de puntos iniciales desde manejador  "
			<< puntos_iniciales.size() << endl;

	//obtiene semillas:
	this->semillas = this->buckShot(cantidad_de_semillas, puntos_iniciales);
	//this->semillas = puntos_iniciales;
	cout << "cantidad de semillas para la muestra " << cantidad_de_semillas
			<< " size: " << semillas.size() << endl;

	//K-Means:
	KMeans instancia_KMeans = KMeans(this->puntos_muestra, 0,
			this->semillas, multiPertenencia); //MAX_ITERACIONES = 0, DEFINIR.
	(&instancia_KMeans)->calcularClusters();
	this->lista_de_clusters = instancia_KMeans.getClusters();

	//CLASIFICAR LOS DEMAS PUNTOS:
	//creo lista de indices de los puntos que no estan en la muestra
	vector<int> indices_no_muestreados = this->indices_no_muestreados(
			cantidad_docs_total, indices_muestra);

	//Genero lista de puntos no muestreados:		

	vector<Punto> lista_no_muestreados = this->manejador->LevantarListaDePuntos(
			indices_no_muestreados, vectorArchivos);
	cout << "No Muestreados.. size: " << lista_no_muestreados.size() << endl;

	//Clasifico cada uno de esos puntos:
	for (unsigned int j = 0; j < lista_no_muestreados.size(); j++) {
		this->Clasificar(lista_no_muestreados[j]);
	}
	//ya tengo todos los clusters armados.
	delete this->manejador;
}

/**********************************************************************/
/**********************************************************************/

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

/**********************************************************************/
/**********************************************************************/

// (*) UNA VEZ QUE YA TENGO EL NUEVO PUNTO:
// Recibe la lista_de_clusters del Clustering y el nuevo punto ya creado.
void Clustering::Clasificar(Punto nuevo_punto) {
	cout << "CLASIFICAR EN CLUSTERING" << endl;
	cout << "doc, nombre :" << nuevo_punto.getDocumento() << " , "
			<< nuevo_punto.getNombreDoc() << endl;
	vector<Cluster*> cluster_destino; //lista de los clusters donde se va a agregar el nuevo punto.
	vector<Cluster*> lista_de_clusters = this->lista_de_clusters;
	// Primero busco cual es la minima distancia.
	double minima_distancia =
			lista_de_clusters[0]->getCentroide().distanciaCoseno(nuevo_punto);
	for (unsigned int i = 1; i < lista_de_clusters.size(); i++) {
		if (lista_de_clusters[i]->getCentroide().distanciaCoseno(nuevo_punto)
				< minima_distancia) {
			minima_distancia =
					lista_de_clusters[i]->getCentroide().distanciaCoseno(
							nuevo_punto);
		}
	}
	// Despues busco cuales son los clusters que tienen esa minima distancia:
	for (unsigned int j = 0; j < lista_de_clusters.size(); j++) {
		if (lista_de_clusters[j]->getCentroide().distanciaCoseno(nuevo_punto)
				== minima_distancia) {
			cluster_destino.push_back(lista_de_clusters[j]);
		}
	}
	// Agrego el punto a los clusters de la lista si puede estar en mas de un cluster
	// o solo al primer cluster de la lista si solo puede esta en un cluster
	if (this->multiPertenencia == true) {
		for (unsigned int x = 0; x < cluster_destino.size(); x++) {
			cluster_destino[x]->agregarElemento(nuevo_punto); //agregar Clasificacion
		}
		for (unsigned int x = 0; x < cluster_destino.size() ; x++){
			cluster_destino[x]->agregarElemento(nuevo_punto); //agregar Clasificacion
		}
	
		cluster_destino[0]->agregarElemento(nuevo_punto);
	} else {
		cluster_destino[0]->agregarElemento(nuevo_punto);
	}

}

/**********************************************************************/
/**********************************************************************/

vector<Cluster*> Clustering::getListaClusters() {
	return this->lista_de_clusters;
}

/**********************************************************************/
/**********************************************************************/

/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
 * tomaron como muestra para hacer el clutering*/
vector<int> Clustering::obtener_muestra(int cantidad_de_puntos,
		int cantidad_docs) {
	int numero, random;
	cout << "tam muestra :" << cantidad_de_puntos << endl;
	vector<int> lista_de_punteros;
	int i = 0;
	//cout<< "CANT PUNTOS, CANT DOCS : "<<cantidad_de_puntos<<" , "<< cantidad_docs;
	while (i < cantidad_de_puntos) {
		bool agregar = true;
		//cout<<"dentro de while"<<endl;
		// obtain a seed from the system clock:
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 generator(seed);
		numero = generator();
		random = abs(numero % (cantidad_docs));
		//cout << "random : "<<random<<" ";
		/*if (i == 0) {
		 lista_de_punteros.push_back(random);
		 i++;
		 }*/
		for (unsigned int j = 0; j < lista_de_punteros.size(); j++) {
			if (lista_de_punteros[j] == random) {
				//continue;
				agregar = false;
			}
		}
		if (agregar == true) {
			lista_de_punteros.push_back(random);
			i++;
		}
	}
	cout << "fin obtener_muestra\n";
	for (unsigned int g = 0; g < lista_de_punteros.size(); g++){
	cout<<lista_de_punteros[g]<<" - ";  }
	cout<<endl;
	return lista_de_punteros;

}

/**********************************************************************/
/**********************************************************************/

/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
 * agarraron de manera aleatoria para agrupar con el clustering jerarquico aglomerativo  */
vector<int> Clustering::obtener_puntos_random(int cantidad_de_semillas, vector<int> docs_muestra) {
	int numero, random;
	vector<int> lista_de_punteros;
	unsigned int i = 0;
	//cout<<"sqrt; "<<sqrt(cantidad_de_semillas * docs_muestra.size())<<endl;

	while (i < sqrt(cantidad_de_semillas * docs_muestra.size())) {
		bool agregar = true;
		// obtain a seed from the system clock:
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 generator(seed);
		numero = generator();
		random = abs(numero % (docs_muestra.size()));
		//	cout << "randomM : "<<random<<" ";
		/*if (i == 0) {
		 lista_de_punteros.push_back(random);
		 i++;
		 }*/
		for (unsigned int j = 0; j < lista_de_punteros.size(); j++) {
			if (lista_de_punteros[j] == docs_muestra[random]) {
				//continue;
				agregar = false;
			}
		}
		if (agregar == true) {
			lista_de_punteros.push_back(docs_muestra[random]);
			i++;
		}
	}

	cout << "fin obtener_puntos_random\n";
	for (unsigned int g = 0; g < lista_de_punteros.size(); g++){
	cout<<lista_de_punteros[g]<<" , ";  }
	cout<<endl;
	return lista_de_punteros;

}

/**********************************************************************/
/**********************************************************************/

/* CON LA LISTA DE PUNTEROS, SE CARGAN ESOS PUNTOS A MEMORIA Y SE GUARDAN EN UNA LISTA QUE RECIBE BUCKSHOT*/

/* Recibe cantidad de semillas que se quiere y lista de los raiz(K.N) puntos a procesar.
 * Devuelve las K semillas que se usaran en el K-Means. */
vector<Punto> Clustering::buckShot(unsigned int cantSemillas,
		vector<Punto> lista_puntos) {

	/* comparar cada uno de los puntos de de la lista con los demas para ver cual es el mas cercano.
	 * de a uno por vez, en cada paso del for comparo solo apartir de i+1 para no repetir comparaciones.
	 * Guardo en una arista (v1,v2,distancia,i1,i2) y comparo las distancias. siendo i1, i2 indices.
	 * Tomo los v1 y v2 con menor distancia, los saco de la lista de puntos y agrego un nuevo punto
	 * que es el promedio de ambos. Vuelvo a empezar con largo -1 y asi hasta tener largo = cantSemillas*/

	unsigned int i, j;
	vector<Arista*> lista_aristas;
	Arista arista, menor_arista;
	double distancia;
	Punto nuevo_punto;
	cout << "BUCKSHOT: size de lista de puntos:" << lista_puntos.size() << endl;
	while (lista_puntos.size() > cantSemillas) {
		for (i = 0; i < lista_puntos.size(); i++) {
			Punto actual = lista_puntos[i];

			for (j = i + 1; j < lista_puntos.size(); j++) {
				distancia = actual.distanciaCoseno(lista_puntos[j]);
				arista = Arista(actual, lista_puntos[j], distancia, i, j);
				lista_aristas.push_back(&arista);
			}
		}
		menor_arista = arista.buscar_minimo(lista_aristas);
		//creo un nuevo punto que se va a situar en el medio de los dos con menor distancia:
		nuevo_punto = (menor_arista).buscar_promedio();
		//elimino los dos puntos que tenian menor distancia e inserto su promedio:
		lista_puntos.erase(lista_puntos.begin() + ((menor_arista).getI1()));
		lista_puntos.erase(lista_puntos.begin() + ((menor_arista).getI2()));
		lista_puntos.push_back(nuevo_punto);
	}
	return lista_puntos;
}

/**********************************************************************/
/**********************************************************************/

vector<int> Clustering::indices_no_muestreados(int cantidad_docs_total,
		vector<int> indices_muestra) {
	vector<int> indices_no_muestreados;
	std::sort(indices_muestra.begin(), indices_muestra.end());

	int i = 0, indice = 0;

	while (((unsigned)i < (unsigned)cantidad_docs_total) && ((unsigned)indice < (unsigned)indices_muestra.size())) {
		int numero_doc_muestra = indices_muestra[indice];
		if (i == numero_doc_muestra) {
			//cout<<"no muestreado"<<endl;
			if((unsigned)indice<(unsigned)indices_muestra.size()-1)indice++;
		} else {
			indices_no_muestreados.push_back(i);
		}
		i++;
	}
	cout<<"fin indices no muestreados\n";
	for (unsigned int x= 0; x < indices_no_muestreados.size(); x++){
		cout<<indices_no_muestreados[x]<<" - "; }
	cout<< endl;	
	return indices_no_muestreados;
}

/**********************************************************************/
/**********************************************************************/

void Clustering::persistirClusters() {

	ofstream archivoClusters;
	archivoClusters.open(DIR_FILE_CLUSTERS, ios_base::out | ios_base::app);
	vector<Punto> puntosDelCluster;
	string nombreDoc;
	Punto centroide;
	//Cada iteracion es un cluster distinto
	for (unsigned int i = 0; i < lista_de_clusters.size(); i++) {
		centroide = (lista_de_clusters[i])->getCentroide();
		//Tamanio del vector, lo indico para saber hasta donde leer despues
		archivoClusters << centroide.vectorDeFrecuencias().size() << ",";

		//Escribo las componentes del centroide del cluster nro i
		for (unsigned int j = 0; j < centroide.vectorDeFrecuencias().size();
				j++)
			archivoClusters << centroide.vectorDeFrecuencias()[j] << ",";

		//Escribo los nombres y nros de documentos correspondiente a los
		//puntos contenidos en el cluster
		puntosDelCluster = lista_de_clusters[i]->getPuntos();
		for (unsigned int k = 0; k < puntosDelCluster.size(); k++) {
			archivoClusters << puntosDelCluster[k].getNombreDoc() << ",";
			archivoClusters << puntosDelCluster[k].getDocumento() << ",";
		}
		archivoClusters << "/"; //Caracter separador de clusters
	}
	cout<<"fin del persistir..."<<endl;
	archivoClusters.close();
}

/*********************************************************************/
/*********************************************************************/

void Clustering::levantarClusters() {

	vector<float> frecCentroide;
	vector<Punto> puntosDelCluster;
	Punto centroide;
	string auxLinea;
	char* valor;
	char* aux;
	char* longitud;
	string nombreDoc;
	int nroDoc;
	Punto nuevoPunto;
	Cluster nuevoCluster;
	int i, j, n, longCentroid = 0;
	ManejadorArchivos* manejador = new ManejadorArchivos(); //posible perdida de memoria.
	manejador->abrirLectura(DIR_FILE_CLUSTERS);
	n = 0;

	//Cada iteracion es un cluster distinto
	while (this->manejador->leerUnaLineaIndice(auxLinea)) {

		char *linea = new char[102400];
		strcpy(linea, auxLinea.c_str());
		i = 0;

		//Leo la longitud del centroide para saber hasta donde leer
		longitud = strtok(linea, ",");
		longCentroid = atoi((char*) longitud);
		//Recupero el centroide del cluster actual
		while (i < longCentroid) {
			valor = strtok(NULL, ", ");
			frecCentroide[i] = atof(valor);
			i++;
		}

		j = 0;
		while (aux != NULL) {
			aux = strtok(NULL, ", ");
			nombreDoc = aux;
			nroDoc = atof(strtok(NULL, ", "));
			if (aux != NULL)
				puntosDelCluster[j] =Punto(nroDoc, nombreDoc);
			j++;
		}
		centroide = Punto(frecCentroide, nroDoc, nombreDoc);
		nuevoCluster = Cluster(centroide, puntosDelCluster);
		this->lista_de_clusters[n] = &nuevoCluster;
		n++;
		delete[] linea;
	}
	delete manejador;

}

