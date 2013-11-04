/*
 * LectorDirectorios.h
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#ifndef LECTORDIRECTORIOS_H_
#define LECTORDIRECTORIOS_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

class LectorDirectorios {
public:
	LectorDirectorios();
	virtual ~LectorDirectorios();
	// se le entrega una ruta y devuelve una lista de archivos en ese directorio
	// devuelve NULL ante algun problema
	vector<string>& leerDir(const char* ruta);
};

#endif /* LECTORDIRECTORIOS_H_ */
