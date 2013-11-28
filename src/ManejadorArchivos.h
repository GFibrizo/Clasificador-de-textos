/*
 * ManejadorArchivos.h
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_


#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <ios>
#include "Punto.h"
#define DIR_STOP_WORDS "sistema/stop_words"
#define DIR_FILE_HASH_2 "sistema/file_hash2"
#define DIR_FILE_INDICE_FINAL "sistema/indiceDocumentos"

//#include "PreProcesarDatos.h"

using namespace std;

class ManejadorArchivos {
private:

   std::fstream  miarchivo;  // mi archivo

public:

  //Constructor
  ManejadorArchivos();
  //Destructor
  ~ManejadorArchivos();

  void cerrarArchivo();		

  void abrirLectura(const string& miruta);

  bool leerUnaLinea(string& micadena);

  bool leerUnaLineaIndice(string& micadena);

  void terminarLinea();

  bool estaAlFinal();

  char* leerArchivo();
  //Recibe un vector con numeros de docs, lee el archivo del hash secundario y crea y devuelve la lista de puntos correspondiente.
  vector<Punto> LevantarListaDePuntos(vector<int> numero_doc, vector<string> vectorArchivos);

};
#endif /* MANEJADORARCHIVOS_H_ */
