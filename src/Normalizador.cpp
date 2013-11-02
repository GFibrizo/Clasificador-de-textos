/*
 * NormalizarLetra.cpp
 *
 *  Created on: 30/10/2013
 *      Author: agu
 */

#include "Normalizador.h"



Normalizador::Normalizador() {
	// TODO Auto-generated constructor stub

}

Normalizador::~Normalizador() {
	// TODO Auto-generated destructor stub
}


std::string Normalizador::stringMinuscula(std::string& palabra){

	 transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
	return palabra;
}

//CANCELADO:
char Normalizador::normalizarLetra(char letra){
	char temp;
	//si no es una letra y no es espacio, retorno NULL
	if(!isalpha(letra) && !isspace(letra)){
		//TODO Ver null,por ahora retorna 0
		//temp= NULL;
		temp='z';

	}else{
		//Si es letra verifico si esta o no en mayuscula
		if(isalpha(letra)){
			//si esta en mayuscula retorno la letra en minuscula
			if(isupper(letra)){
				temp= tolower(letra);
			}else{
				temp= letra;
			}

		}
		//si es un espacio, retorno el mismo espacio
		if(isspace(letra)){
			temp= letra;
		}

	}

	return temp;
}
