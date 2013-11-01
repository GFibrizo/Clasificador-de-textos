#ifndef LECTOR_DIRECTORIOS_H_
#define LECTOR_DIRECTORIOS_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

class Lector_directorios{

	public:
	// se le entrega una ruta y devuelve una lista de archivos en ese directorio
	// devuelve NULL ante algun problema
	std::vector<std::string>& leer_dir(const char* ruta);

};
#endif
