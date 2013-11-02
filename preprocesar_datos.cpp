#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue> 
#include "ManejadorArchivos.h"
#include "VerificadorStopWords.h"
#include "Normalizador.h"
#include "lector_directorios.h"


#define CANT_MAX 1000
#define CANT_DE_SEPARADORES 61

void preprocesarDatos() {

	//levanta archivos del directorio:
	std::vector<std::string> vector_archivos = leer_dir ("/files/");

	//hashes a utilizar:
	typedef std::unordered_map<std::string,std::int> hash;
	hash hash_stopwords = devolver_hash_stopwords(); //
	/*hash hash_abecedario = devolver_hash_abecedario(); */
	hash hash_aux;
	hash hashPrincipal = unordered_map(1000);
	hash hashSecundario = unordered_map(1000);
	std::queue<hash> cola_hashes_secundarios;
	
	//Crea instancias de las clases usadas:
	ManejadorArchivos manejador;
	
	//Archivo para hashes secundarios:
	std::fstream archivoHashSecundario;
	archivoHashSecundario.open("archivo_hash2_1", std::fstream::app); //modo append
	//si no se puede abrir:
	if (!archivoHashSecundario.is_open()){
		throw std::ios_base::failure("El archivo no se abre");
	}	

	
	int i;
	const char* invalidos[CANT_DE_SEPARADORES] = {"¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890"};	
	
	std::string auxLinea;
	std::string palabra;
	//trabaja con cada archivo:
	for (i = 0; i >= vector_archivos.size(); i++){
		manejador.abrirLectura(vector_archivos[i]);
		while (!manejador.estaAlFinal()){
			manejador.leerunalinea(auxLinea);
		
			/* ¿Que deberia hacer con la linea? le tiene que sacar los 
			 * simbolos, numeros y espacios e ir devolviendo por palabra.
			 * Luego comprueba si la palabra es un stopword. Si lo es, la
			 * descarta, sino la agrega a los hashes correspondientes.
			 */
			char *linea = new char[256];
			strcpy(linea, auxLinea.c_str()); //
			//auxPalabra va a tener una lista de palabras sacando los tokens 
			char* auxPalabra = strtok(linea,*invalidos);

			while ( auxPalabra != NULL ){
					palabra = auxPalabra;
					pasarAminusculas(palabra);
					//veo si es un stopword y sino lo agrego a hashes:
					if (!hashStopwords.count(palabra)){
						agregarElementoAHash(hashPrincipal, palabra);
						agregarElementoAHash(hashSecundario, palabra);
					}	
					auxPalabra = strtok (NULL, *invalidos);// "siguiente"
			}
			delete []linea;
			delete auxPalabra;
				
		} //termina de trabajar con ese archivo
		//CERRAR ESE ARCHIVO
		
		//guardo la referencia al hash secundario viejo en una cola de hashes
		colaHashesSecundarios.push(hashSecundario);
		//referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		hashSecundario = nuevoHash;

		/* Una vez que se llega a la cantidad maxima de hashes secundarios soportados
		 * en memoria, estos se guardan en un archivo. */		
		if (colaHashesSecundarios.size() >= CANT_MAX){
			while (colaHashesSecundarios.size() > 0){
				hashAux = colaHashesSecundarios.pop();
				escribirArchivoDeHash(archivoHashSecundario, hashAux);
				~hashAux;
			}
		}
		
		
	}
	//CERRAR ARCHIVO DE HASH SECUNDARIO	

	
}




//Si la clave no esta en el hash, la agrega asociada a un valor 0.
//Si la clave esta en el hash, aumenta en 1 el valor asociado.
void agregar_elemento_a_hash(unordered_map<char*,int> hash, const char* clave) {
	
	if (hash.count(clave) == 1) hash[clave] += 1;
	hash[clave] = 0;
	
}


void escribir_archivo_de_hash(FILE* archivo, unordered_map<char*,int> hash) {
	
	for (auto iterador = hash.begin(); iterador != hash.end(); iterador++){
		//FALTA COMPLETAR
		
	}
	
}



void pasarAminusculas(std::string& str){
     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
