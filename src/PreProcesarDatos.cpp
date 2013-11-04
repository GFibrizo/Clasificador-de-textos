/*
 * PreProcesarDatos.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#include "PreProcesarDatos.h"


PreProcesarDatos::PreProcesarDatos(const char* ruta) {
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890";//[CANT_DE_SEPARADORES]
	LectorDirectorios * lecDirectorio= new LectorDirectorios();
	//levanta archivos del directorio:
	this->vector_archivos = lecDirectorio->leerDir (ruta);
	this->verifStopWord= new VerificadorStopWords(DIR_STOP_WORDS);
	this->manejador = new ManejadorArchivos() ;
	this->hashPrincipal= tr1::unordered_map(1000);
	this->hashSecundario= tr1::unordered_map(1000);
	this->archivoHashSecundario.open(DIR_FILE_HASH_2, fstream::app); //modo append
		//si no se puede abrir:
		if (!this->archivoHashSecundario.is_open()){
			throw std::ios_base::failure("El archivo no se abre");
		}

}

PreProcesarDatos::~PreProcesarDatos() {

	delete this->verifStopWord;
	delete this->manejador;
	archivoHashSecundario.close();
}
void PreProcesarDatos::pasarAminusculas(string& str){
     transform(str.begin(), str.end(), str.begin(), ::tolower);
}

//Si la clave no esta en el hash, la agrega asociada a un valor 0.
//Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::agregarElementoAHash(hash hash, string clave){

//	if (hash.count(clave) == 1) hash[clave] += 1;
//	hash[clave] = 0;

}


void PreProcesarDatos::escribirArchivoDeHash(hash hash){

//	for (auto iterador = hash.begin(); iterador != hash.end(); iterador++){
//		//FALTA COMPLETAR
//
//	}
}

void PreProcesarDatos::preProcesarDatos(){
	string auxLinea;
	string palabra;
	//trabaja con cada archivo:
	unsigned int i;
	for (i = 0; i <= this->vector_archivos.size(); i++){
		this->manejador->abrirLectura(this->vector_archivos[i]);
		while (!this->manejador->estaAlFinal()){
			this->manejador->leerUnaLinea(auxLinea);

			/* ¿Que deberia hacer con la linea? le tiene que sacar los
			 * simbolos, numeros y espacios e ir devolviendo por palabra.
			 * Luego comprueba si la palabra es un stopword. Si lo es, la
			 * descarta, sino la agrega a los hashes correspondientes.
			 */
			char *linea = new char[256];
			strcpy(linea, auxLinea.c_str()); //
			//auxPalabra va a tener una lista de palabras sacando los tokens
			char* auxPalabra = strtok(linea,this->invalidos);

			while ( auxPalabra != NULL ){
					palabra = auxPalabra;
					pasarAminusculas(palabra);
					//veo si es un stopword y sino lo agrego a hashes:
					if(this->verifStopWord->verificarPalabra(palabra)){
						cout<<palabra;
						agregarElementoAHash(this->hashPrincipal, palabra);
						agregarElementoAHash(this->hashSecundario, palabra);
					}
					auxPalabra = strtok (NULL, this->invalidos);// "siguiente"
			}
			delete []linea;
			delete auxPalabra;

		} //termina de trabajar con ese archivo
		//CERRAR ESE ARCHIVO

		//guardo la referencia al hash secundario viejo en una cola de hashes
		this->colaHashesSecundarios.push(this->hashSecundario);
		//referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		this->hashSecundario = nuevoHash;

		/* Una vez que se llega a la cantidad maxima de hashes secundarios soportados
		 * en memoria, estos se guardan en un archivo. */
		if (this->colaHashesSecundarios.size() >= CANT_MAX){
			while (this->colaHashesSecundarios.size() > 0){
				//TODO incorrecto el modo de asignacion
				//this->hashAux.insert(this->colaHashesSecundarios.pop());; // = this->colaHashesSecundarios.pop();
				escribirArchivoDeHash(this->hashAux);
			}
		}


	}
	//CERRAR ARCHIVO DE HASH SECUNDARIO

}

const char* PreProcesarDatos::getInvalidos(){
	return this->invalidos;
}
