/*
 * ManejadorArchivos.h
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_

#define DIR_FILE_HASH_2 "sistema/file_hash2"
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <ios>
#include "Punto.h"

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

  bool leerUnaLineaIndice(string& micadena);

  void terminarLinea();

  bool estaAlFinal();

  char* leerArchivo();
  //Recibe un vector con numeros de docs, lee el archivo del hash secundario y crea y devuelve la lista de puntos correspondiente.
  vector<Punto*> GenerarListaDePuntos(vector<int> numero_doc);

};
#endif /* MANEJADORARCHIVOS_H_ */
