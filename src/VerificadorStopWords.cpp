/*
 * VerificadorStopWords.cpp
 *
 *  Created on: 28/10/2013
 *      Author: agu
 */

#include "VerificadorStopWords.h"


//constructor: levanta el archivo de stopwords
VerificadorStopWords::VerificadorStopWords(std::string ruta) {

		ManejadorArchivos archivo;
		archivo.abrirLectura(ruta);
		std::string lineaaux;

		while(archivo.leerunalinea(lineaaux)){
			this->tabla.insert(lineaaux);
		}

}

bool VerificadorStopWords::verificarPalabra(std::string palabra){

	if(tabla.count(palabra)==0){
		return false;
	}
	return true;
}

VerificadorStopWords::~VerificadorStopWords() {
	// TODO Auto-generated destructor stub
}

