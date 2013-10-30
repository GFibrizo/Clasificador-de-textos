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

class ManejadorArchivos {
private:

   std::fstream  miarchivo;  // mi archivo

public:

  //Constructor
  ManejadorArchivos();
  //Destructor
  ~ManejadorArchivos();

  void abrirLectura(const std::string& miruta);

  bool leerunalinea(std::string& micadena);

  void terminarlinea();

};
#endif /* MANEJADORARCHIVOS_H_ */
