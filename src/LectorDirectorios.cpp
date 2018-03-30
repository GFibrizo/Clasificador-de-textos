/*
 * LectorDirectorios.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#include "LectorDirectorios.h"

/**********************************************************************/
/**********************************************************************/


LectorDirectorios::LectorDirectorios() {
	// TODO Auto-generated constructor stub
}

/**********************************************************************/
/**********************************************************************/


LectorDirectorios::~LectorDirectorios() {
	// TODO Auto-generated destructor stub
}

/**********************************************************************/
/**********************************************************************/


vector<string> LectorDirectorios::leerDir(const char* ruta){
	DIR *dir = NULL;
	struct dirent *drnt = NULL;
	vector<string> archivos;
	const char* puntos = ".";
	const char* puntos2 = "..";
	dir=opendir(ruta);

	if(dir){
		int i=0;
		while((drnt = readdir(dir))){
			if((strcmp(drnt->d_name,puntos)==0) || ((strcmp(drnt->d_name,puntos2)==0))) continue;
			stringstream ss;
			ss<<drnt->d_name;
			string aux (ss.str());
			archivos.push_back(aux);
			i++;
    }
    closedir(dir);
	}
	return archivos;
}
