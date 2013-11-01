/*
 * ManejadorArchivos.h
 *
 *  Created on: 25/05/2013
 *      Author: pablo
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <ios>

class ManejadorArchivos {
private:

   std::fstream  miarchivo;  // mi archivo

public:

  //Constructor
  ManejadorArchivos();
  //Destructor
  ~ManejadorArchivos();

  void abrirLectura(const std::string& miruta);

  bool leerUnaLinea(std::string& micadena);

  void terminarLinea();

  bool estaAlFinal();

};
#endif /* MANEJADORARCHIVOS_H_ */
