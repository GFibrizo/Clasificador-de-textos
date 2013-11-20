/*
 * ManejadorArchivos.h
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <ios>
using namespace std;
class ManejadorArchivos {
private:

   std::fstream  miarchivo;  // mi archivo

public:

  //Constructor
  ManejadorArchivos();
  //Destructor
  ~ManejadorArchivos();

  void abrirLectura(const string& miruta);

  bool leerUnaLinea(string& micadena);

  void terminarLinea();

  bool estaAlFinal();

  char* leerArchivo();

};
#endif /* MANEJADORARCHIVOS_H_ */
