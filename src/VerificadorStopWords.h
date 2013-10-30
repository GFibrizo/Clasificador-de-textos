/*
 * VerificadorStopWords.h
 *
 *  Created on: 28/10/2013
 *      Author: agu
 */

#ifndef VERIFICADORSTOPWORDS_H_
#define VERIFICADORSTOPWORDS_H_
#include <tr1/unordered_set>
#include "ManejadorArchivos.h"


class VerificadorStopWords {
private:
	std::tr1::unordered_set<std::string> tabla;
public:
	VerificadorStopWords(std::string ruta);
	virtual ~VerificadorStopWords();
	bool verificarPalabra(std::string);
};


#endif /* VERIFICADORSTOPWORDS_H_ */
