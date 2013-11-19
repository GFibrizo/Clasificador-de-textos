#include "JerarquicoAglomerativo.h"

JerarquicoAglomerativo::JerarquicoAglomerativo() {
	// TODO Auto-generated constructor stub
}

JerarquicoAglomerativo::~JerarquicoAglomerativo() {
	// TODO Auto-generated destructor stub
}

Arista::Arista(v1,v2,distancia,i1,i2){
	this->v1 = v1;
	this->v2 = v2;
	this->distancia = distancia;
	this->i1 = i1;
	this->i2 = i2;	
}

Arista::~Arista(){ }	

double Arista::distancia(){
	return this->distancia;
}

Punto Arista::v1(){
	return this->v1;
}

Punto Arista::v2(){
	return this->v2;
}

int Arista::i1(){
	return this->i1;
}

int Arista::i2(){
	return this->i2;
}


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
vector<Punto> JerarquicoAglomerativo::buckShot(int cantDocs,int cantSemillas,  vector<Punto> lista_puntos){
/* comparar cada uno de los puntos de de la lista con los demas para ver cual es el mas cercano.
 * de a uno por vez, en cada paso del for comparo solo apartir de i+1 para no repetir comparaciones.
 * Guardo en una arista (v1,v2,distancia,i1,i2) y comparo las distancias. siendo i1, i2 indices.
 * Tomo los v1 y v2 con menor distancia, los saco de la lista de puntos y agrego un nuevo punto 
 * que es el promedio de ambos. Vuelvo a empezar con largo -1 y asi hasta tener largo = cantSemillas*/
	int i,j;
	vector<Arista> lista_aristas;
	Arista::Arista arista, menor_arista;

	while (lista_puntos.size() > cantSemillas){
		for (i = 0; i < lista_puntos.size(); i++){
		Punto actual = lista_puntos[i];
			for (j = i+1; j < lista_puntos.size(); j++){
				double distancia = Distancia::distanciaCoseno(actual, lista_puntos[j]);
				arista = Arista::Arista(actual, lista_puntos[j],distancia, i,j);
				lista_distancias.push_back(arista);
			}
		}
		menor_arista = buscar_minimo(lista_aristas);
		//creo un nuevo punto que se va a situar en el medio de los dos con menor distancia:
		Punto nuevo_punto = buscar_promedio(menor_arista);
		//elimino los dos puntos que tenian menor distancia e inserto su promedio:
		lista_puntos.erase(lista_puntos.begin()+(menor_arista.i1()));
		lista_puntos.erase(lista_puntos.begin()+(menor_arista.i2()));
		lista_puntos.push_back(nuevo_punto);
	}
	return lista_puntos;
}

	

Arista::Arista buscar_minimo(vector<Arista> lista_aristas){
	double minimo = lista_aristas[0].distancia();
	Arista::Arista menor_arista;
	int i;
	for (i=1; i < lista_aristas.size(); i++){
		if (lista_aristas[i].distancia() < minimo){
			minimo = lista_aristas[i].distancia();
			menor_arista = lista_arista[i];
		}
	}
	return menor_arista;	
}

Punto::Punto buscar_promedio(Arista::Arista arista){
	Punto nuevo_punto = Punto; //VER COMO SE CREA.
	/*Extraigo arista.v1() y arista.v2(), tengo que saber como funciona la clase Punto
	 * para extraer sus vectores y calcular el punto medio v1+v2  / 2. */
		
	return nuevo_punto	
}		





int main(){
	return 0;
}
