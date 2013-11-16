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
#include <cstring>
#include <tr1/unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include "ManejadorArchivos.h"
#include "VerificadorStopWords.h"
#include "LectorDirectorios.h"
#include "Porter.h"


#define CANT_MAX 3//1000
#define CANT_DE_SEPARADORES 61
//TODO Tratar de tener separados los directorios donde se utilicen archivos que utiliza el sistema
#define DIR_STOP_WORDS "sistema/stop_words"
#define DIR_FILE_HASH_2 "sistema/file_hash2"

using namespace std;


class PreProcesarDatos {
private:
	typedef struct {
			int frecuencia;
			int documentos;
		}t_datosHash;
		//hashes a utilizar:
		typedef tr1::unordered_map<string,t_datosHash> t_hashPrincipal;
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
	int  verifDocDiferentes;
	string directorio;

	void pasarAminusculas(string& str);
	void escribirArchivoDeHash(hash hash);
	void agregarElementoAHash(hash& hash, string clave);
	string numberToString(int number);
	void generarArchivoConDatosPonderados();
	string stem_palabra(string palabra);
	void agregarElementoAHashPrincipal(t_hashPrincipal& hash,string palabra,int numDoc);
	void relative_dir_base_split(const string& path, string& dir);
public:
	PreProcesarDatos(const char* ruta);
	virtual ~PreProcesarDatos();
	void preProcesarDatos();


};

#endif /* PREPROCESARDATOS_H_ */
