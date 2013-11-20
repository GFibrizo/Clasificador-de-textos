/*
 * ManejadorArchivos.cpp
 */

#include "ManejadorArchivos.h"
#include <iostream>
#include <string.h>

using namespace std;

ManejadorArchivos::ManejadorArchivos(){}


/**
  * Destructor del ManejadorArchivos:
  * Cierra el archivo unicamente, no lo destruye
  */
ManejadorArchivos::~ManejadorArchivos() {
  miarchivo.close();
}

/*Abre el archivo pasado por parametro
 * en modo LECTURA
 */
void ManejadorArchivos::abrirLectura(const string &nombre){


	//intenta abrir el archivo en modo lectura
	  miarchivo.open(nombre.c_str(), fstream::in); //in = read.

	  if (!miarchivo.is_open())
	          // si no se puede abrir
	          throw ios_base::failure("El archivo "+nombre+" no se abre");

	}


//void ManejadorArchivos::abrirEscritura(const std::string& miruta){

//	miarchivo.open(miruta.c_str(), std::fstream::in);
//}


// Lo que lee lo guardo en micadena
// Retorna true si pudo leer una linea, o false en caso contrario
bool ManejadorArchivos::leerUnaLinea(string &micadena){

	
	char linea[512];

	  // lee del archivo a la linea, hasta haber leido
	  // MAX_LENGTH caracteres(en este caso 100 kbytes
	  miarchivo.getline( (char*)&linea , 512);
	  micadena = linea;

	  if (miarchivo.fail() ) {
	    //chequea si se ha producido un error, se devuelve false
	    miarchivo.clear();
	    return false;
	  }
	  return true;



}

/**
 * Posiciona el cursor en una nueva linea debajo de la actual
 *
 */
void ManejadorArchivos::terminarLinea() {
  // intenta escribir en el archivo
  miarchivo << endl;

  if (miarchivo.fail())
    //si se produjo un error, arroja una excepcion
    throw ios_base::failure("No se pudo terminar la linea");
}

bool ManejadorArchivos::estaAlFinal(){
	
	return miarchivo.eof();
	
}

char* ManejadorArchivos::leerArchivo(){
	
    miarchivo.seekg (0, miarchivo.end);
    int largo = miarchivo.tellg();
    miarchivo.seekg (0, miarchivo.beg);

    char * buffer = new char [largo-1];

    miarchivo.read (buffer,largo-1);
    
    miarchivo.close();

	return buffer;
	
	
}



