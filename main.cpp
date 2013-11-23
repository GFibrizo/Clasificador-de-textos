/*
 * main.cpp
 *
 *  Created on: 25/10/2013
 *      Author: agu
 */




#include <iostream>
#include <string>
#include "src/PreProcesarDatos.h"

using namespace std;


int main (int argc, char **argv) {

	PreProcesarDatos* preDatos = new PreProcesarDatos("files/");
	/*lee los archivos, arma el hash principal y lo guarda como atributo. Arma los hash secundarios y los guarda en archivos.*/
	preDatos->preProcesarDatos();
	
	//2)Tomo muestra de M < N docs random para hacer el clustering: obtengo los numeros de docs. 
	//3)Para cada uno de los indices llama a LeerDatos(numero_de_archivo) que: abre el archivo, lee cada vector, le saca
	//el formato. Crea el punto correspondiente al doc y lo devuelve.
	//4)Dentro de esa muestra se toman sqrt(M.K) puntos; se hace el jerarquico aglomerativo de esos puntos para obtener las
	//k semillas.
	//5) Hace K-means de la muestra.
	//6) Se clasifican los demas documentos (abriendolos de a uno).

	return 0;
}

