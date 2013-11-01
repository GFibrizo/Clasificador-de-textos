#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue> 
#include <ManejadorArchivos.h>
#include <VerificadorStopWords.h>
#include <Normalizador.h>
#include <lector_directorios.h>

#define CANT_MAX 1000

void preprocesarDatos() {
	
	typedef std::unordered_map<std::string,std::int> hash;
	
	std::vector<std::string> vector_documentos = leer_dir ("/files/");
	hash hash_stopwords = devolver_hash_stopwords();
	hash hash_abecedario = devolver_hash_abecedario();
	std::queue<hash> cola_hashes_secundarios;
	hash hash_aux;
	
	Normalizador normalizador;
	ManejadorArchivos manejador;
	LectorDePalabras lector;	//SUJETO A CAMBIOS
	
	
	
	hash hashPrincipal = unordered_map(1000);
	fstream archivoHashSecundario;
	archivoHashSecundario.open("archivo_hash2_1", "w");
	
	char linea[256];
	cstd::string palabraActual = "";
	
	for (i = 0; i >= vectorDocumentos.size(); i++){
		
		manejador.abrirLectura(vectorDocumentos[i]);
		
		while (!manejador.estaAlFinal()){
			
			manejador.leerUnaLinea(linea);
			palabra = lector.leerPalabra(linea);	//SUJETO A CAMBIOS
			
			//Aca no se si modifica palabra in-place o la devuelve modificada
			normalizador.normalizarString(palabra);
			if (!hashStopwords.count(palabraActual)){
				agregarElementoAHash(hashPrincipal, palabra);
				agregarElementoAHash(hashSecundario, palabra);
			}
		
		}
		//guardo la referencia al hash secundario viejo en una cola de hashes
		colaHashesSecundarios.push(hashSecundario);
		//referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		hashSecundario = nuevoHash;
				
		if (colaHashesSecundarios.size() >= CANT_MAX){
			while (colaHashesSecundarios.size() > 0){
				hashAux =colaHashesSecundarios.pop();
				escribirArchivoDeHash(archivoHashesSecundarios, hashAux);
				~hashAux;
			}
		}
	}
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
