#include "JerarquicoAglomerativo.h"

JerarquicoAglomerativo::JerarquicoAglomerativo() {
	// TODO Auto-generated constructor stub
}

JerarquicoAglomerativo::~JerarquicoAglomerativo() {
	// TODO Auto-generated destructor stub
}

Arista::Arista(){ }

//constructor:
Arista::Arista(Punto v1,Punto v2, double distancia,int i1,int i2){
	this->v1 = v1;
	this->v2 = v2;
	this->distancia = distancia;
	this->i1 = i1;
	this->i2 = i2;	
}

//destructor:
Arista::~Arista(){ }	

double Arista::dar_distancia(){
	return this->distancia;
}

Punto Arista::dar_v1(){
	return this->v1;
}

Punto Arista::dar_v2(){
	return this->v2;
}

int Arista::dar_i1(){
	return this->i1;
}

int Arista::dar_i2(){
	return this->i2;
}

using namespace std;

/* Devuelve una lista de los punteros (numero entero que representa al doc) de los documentos que se 
 * agarraron de manera aleatoria para agrupar con el clustering jerarquico aglomerativo  */
vector<int> JerarquicoAglomerativo::obtener_puntos_random(int cantidad_de_puntos, int cantidad_docs){
	int i, numero;
	vector<int> lista_de_punteros;
	for (i = 0; i < cantidad_de_puntos; i++) {	
		// obtain a seed from the system clock:
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		mt19937 generator (seed);
		numero = generator();
		lista_de_punteros.push_back(abs(numero % cantidad_docs));
	}
	return lista_de_punteros;	
}

/* CON LA LISTA DE PUNTEROS, SE CARGAN ESOS PUNTOS A MEMORIA Y SE GUARDAN EN UNA LISTA QUE RECIBE BUCKSHOT*/

/* Recibe cantidad de documentos, cantidad de semillas que se quiere y lista de los raiz(K.N) puntos a procesar.
 * Devuelve las K semillas que se usaran en el K-Means. */
vector<Punto> JerarquicoAglomerativo::buckShot(int cantDocs,unsigned int cantSemillas,  vector<Punto> lista_puntos){
/* comparar cada uno de los puntos de de la lista con los demas para ver cual es el mas cercano.
 * de a uno por vez, en cada paso del for comparo solo apartir de i+1 para no repetir comparaciones.
 * Guardo en una arista (v1,v2,distancia,i1,i2) y comparo las distancias. siendo i1, i2 indices.
 * Tomo los v1 y v2 con menor distancia, los saco de la lista de puntos y agrego un nuevo punto 
 * que es el promedio de ambos. Vuelvo a empezar con largo -1 y asi hasta tener largo = cantSemillas*/
	unsigned int i,j;
	vector<Arista> lista_aristas;
	Arista arista, menor_arista;
	double distancia;
	
	while (lista_puntos.size() > cantSemillas){
		for (i = 0; i < lista_puntos.size(); i++){
		Punto actual = lista_puntos[i];
			for (j = i+1; j < lista_puntos.size(); j++){
				//distancia = Distancia::distanciaCoseno(actual, lista_puntos[j]);
				distancia = actual.distanciaCoseno(lista_puntos[j]);
				arista = Arista::Arista(actual, lista_puntos[j],distancia, i,j);
				lista_puntos.push_back(arista);
			}
		}
		menor_arista = buscar_minimo(lista_aristas);
		//creo un nuevo punto que se va a situar en el medio de los dos con menor distancia:
		Punto nuevo_punto = buscar_promedio(menor_arista);
		//elimino los dos puntos que tenian menor distancia e inserto su promedio:
		lista_puntos.erase(lista_puntos.begin()+(menor_arista.dar_i1()));
		lista_puntos.erase(lista_puntos.begin()+(menor_arista.dar_i2()));
		lista_puntos.push_back(nuevo_punto);
	}
	return lista_puntos;
}

	

Arista::Arista buscar_minimo(vector<Arista> lista_aristas){
	double minimo = lista_aristas[0].dar_distancia();
	Arista::Arista menor_arista;
	int i;
	for (i=1; i < lista_aristas.size(); i++){
		if (lista_aristas[i].distancia() < minimo){
			minimo = lista_aristas[i].dar_distancia();
			menor_arista = lista_arista[i];
		}
	}
	return menor_arista;	
}

/*Extraigo v1 y v2 de la arista, calculo el vector promedio y creo un nuevo punto que devuelvo.*/
Punto::Punto buscar_promedio(Arista::Arista arista){
	vector<double> v1 = arista.dar_v1().vectorDeFrecuencias();
	vector<double> v2 = arista.dar_v2().vectorDeFrecuencias();
	vector<double> frecPond;
	int i;
	for (i = 0; i < v1.size(); i++){
		frecPond[i] = (v1[i] + v2[i]) / 2;	
	}
	Punto nuevo_punto = Punto::Punto(frecPond, -1);
	return nuevo_punto	
}		




