#include "lector_directorios.h"
using namespace std;

vector<string>& Lector_directorios::leer_dir(const char* ruta){

	// variables
	DIR *dir = NULL;
	struct dirent *drnt = NULL;
	vector<string>*archivos = new vector<string>;
	const char* puntos = ".";
	const char* puntos2 = "..";

	dir=opendir(ruta);

	if(dir){

		int i=0;

		while((drnt = readdir(dir))){

			if((strcmp(drnt->d_name,puntos)==0)||((strcmp(drnt->d_name,puntos2)==0))) continue;

			stringstream ss;
			ss<<drnt->d_name;
			string aux (ss.str());
			archivos->push_back(aux);
			i++;
	    }

	    closedir(dir);

	}else{

		delete archivos;
		// devuelve uno vacio
		vector<string>*archivos = new vector<string>;
		return *archivos;
	}

	return *archivos;
}

