/*
 * PreProcesarDatos.h
 *
 *  Created on: 03/11/2013
 *      Author: agu
 *      #include <cstdbool>
 */

#ifndef PREPROCESARDATOS_H_
#define PREPROCESARDATOS_H_

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <tr1/unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include "ManejadorArchivos.h"
#include "VerificadorStopWords.h"
#include "LectorDirectorios.h"


#define CANT_MAX 3//1000
#define CANT_DE_SEPARADORES 61
//TODO Tratar de tener separados los directorios donde se utilicen archivos que utiliza el sistema
#define DIR_STOP_WORDS "sistema/stop_words"
#define DIR_FILE_HASH_2 "sistema/file_hash2"

using namespace std;


class PreProcesarDatos {
private:
	//hashes a utilizar:
	typedef tr1::unordered_map<string,int> hash;
	hash hashAux;
	hash hashPrincipal;
	hash hashSecundario;
	queue<hash> colaHashesSecundarios;
	//fstream archivoHashSecundario;
	ofstream archivoHashSecundario;
	vector<string> vector_archivos;
	const char* invalidos;
	ManejadorArchivos* manejador;
	VerificadorStopWords* verifStopWord;

	void pasarAminusculas(string& str);
	void escribirArchivoDeHash(hash hash);
	void agregarElementoAHash(hash& hash, string clave);
	string numberToString(int number);
public:
	PreProcesarDatos(const char* ruta);
	virtual ~PreProcesarDatos();
	void preProcesarDatos();
	const char* getInvalidos();

};

#endif /* PREPROCESARDATOS_H_ */
