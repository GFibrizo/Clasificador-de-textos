/*
 * PreProcesarDatos.h
 *
 *  Created on: 03/11/2013
 *      Author: agu, fabri
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
#include <cmath>
#include <map>
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

using namespace std;


class PreProcesarDatos {


private:
	typedef struct {
			int frecuencia;
			int documentos;
		}t_datosHash;
		//hashes a utilizar:
		//typedef tr1::unordered_map<string,t_datosHash> t_hashPrincipal;
	typedef map<string,int> hash;
	typedef map<string,float> hash2;	
		
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
	void escribirArchivoIndice(hash2 hash, ofstream& indiceDocumentos);
	void agregarElementoAHash(hash& hash, string clave);
	void agregarElementoAHash(hash2& hash, string clave);
	string numberToString(int number);
	string numberToString(float number);
	void generarIndiceDocumentos();
	string stem_palabra(string palabra);
	void agregarElementoAHashPrincipal(hash& hash,string palabra, bool cambio_doc);
	void relative_dir_base_split(const string& path, string& dir);
	const char* getInvalidos();
	void tokenizar(char* linea);
	//Genera un hash con las claves del hash principal y frecuencia 0.
	hash2 generarHashMemoria();
	float calcular_TF_IDF(string clave, float frecuencia);
public:
	PreProcesarDatos(const char* ruta);
	PreProcesarDatos(hash hashPorParametro);
	virtual ~PreProcesarDatos();
	void preProcesarDatos();
	Punto procesarNuevoDocumento(string ruta);
	map<string, int> obtenerHashVocabulario();
	vector<string> getVectorArchivos();

};

#endif /* PREPROCESARDATOS_H_ */
