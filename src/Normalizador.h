/*
 * Normalizador.h
 *
 *  Created on: 30/10/2013
 *      Author: agu
 */

#ifndef NORMALIZADOR_H_
#define NORMALIZADOR_H_

#include <string>
#include <locale>
#include <algorithm>

class Normalizador {

public:
	Normalizador();
	virtual ~Normalizador();

	/*
	 * @parametro: caracter a normalizar
	 * @return:la letra en minuscula si era una letra, en caso de no haber sido una letra devolver NULL
	 * 			y en caso de ser un espacio, devolver el espacio.
	 */
	char normalizarLetra(char letra);
	/*
	 * @parametro: string &palabra Recibe una referencia a un string
	 * @return: retorna una copia del string normalizada
	 */
	std::string normalizarString(std::string &palabra);
};
#endif /* NORMALIZADOR_H_ */
