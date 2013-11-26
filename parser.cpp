#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#include <iostream>
#include <string>
#include "src/PreProcesarDatos.h"
#include "src/ManejadorArchivos.h"
#include "src/Clustering.h"
#include "src/Punto.h"
#include "src/Cluster.h"

using namespace std;

int main1 (int argc, char **argv) {

	bool l_flag = false; //lista todos los documentos del repositorio y la categoría a la cual pertenece c/u.
	bool g_flag = false; //lista los grupos o categorías existentes y los documentos dentro de cada grupo o categoría.
	
	/* -a : agrega y clasifica el texto pasado como parametro e indica a que grupo lo ha agregado.
	 * 		a partir de aqui debería aparecer al listad con -l o -g. */
	char* a_value = NULL; //Path del nuevo documento.
	
	char *d_value = NULL; //Path de donde tiene guardados los docs.
	char *c_value = NULL; //cantidad de categorias a crear, si es NULL decide solo.
	char *o_value = NULL; // Y/N indica si un documento puede estar en mas de una cateoria.
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "d:c:o:1ga")) != -1) {
		switch (c) {

			case 'd':
				d_value = optarg;
				break;

			case 'c':
				c_value = optarg;
				break;

			case 'o':
				o_value = optarg;
				break;

			case 'l':
				l_flag = true;
				break;

			case 'g':
				g_flag = true;
				break;

			case 'a':
				a_value = optarg;
				break;

			case '?':
				if (optopt == 'd')			fprintf (stderr, "Option -%d requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%d'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				if (optopt == 'c')			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				if (optopt == 'o')			fprintf (stderr, "Option -%o requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%o'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				return 1;
			
			default:
				abort ();
		}
	}

	//Este printf es solo para probar que el parseo anda bien imprimiendo las variables en pantalla
	printf ("d_value = %s, c_value = %s, o_value = %s, l_flag = %d, g_flag = %d, a_value = %s\n", 
																d_value, c_value, o_value, l_flag, g_flag, a_value);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
		
		
		
		
	/* LOGICA */
	
	char* masDeUno = o_value;
	int valor_K; //funcion
	if (d_value != NULL) { 
		PreProcesarDatos* preDatos = new PreProcesarDatos(d_value);
		//lee los archivos, arma el hash principal y lo guarda como atributo. Arma los hash secundarios y los guarda en archivos.
		preDatos->preProcesarDatos();
		cantidad_docs_total = preDatos->getCantDocs(); //TDV NO EXISTE
		
		if (c_value == NULL) 
			valor_K = obtenerKOptimo(cantidad_docs_total);//TDV NO EXISTE
		else
			valor_K = atoi(c_value);
		clustering =  Clustering::Clustering(valor_K, cantidad_docs_total, 0.10 * cantidad_docs_total, masDeUno);//TDV NO MODIFICADO
		
	}else{
		if (a_value != NULL){
			Punto nuevo_punto = PreProcesarDatos::AgregarElemento(a_value); //TDV NO EXISTE
			clustering->Clasificar(nuevo_punto);
		}
		if (l_flag != false){
			// Lista todos los documentos del repositorio y la categoría a la cual pertenece cada uno.
			vector<Cluster*> lista_de_clusters = clustering.getListaClusters();
			for (unsigned int i = 0; i < lista_de_clusters.size() ; i++){
				vector<Punto> puntos_cluster = (*(lista_de_clusters[i])).getPuntos();
				for (unsigned int j = 0; j < puntos_cluster.size(); j++){
					int numeroDoc = puntos_cluster[j]->getDocumento();
					char* nombreDoc = ManejadorArchivos::ObtenerNombreDoc(numeroDoc);//TDV NO EXISTE
					cout<<nombreDoc<<" , categoria:"<<i<<"\n";
				}	
			}	
		}
		if (g_flag != false){
			// Lista los grupos o categorías existentes y los documentos dentro de cada grupo o categoría 
			vector<Cluster*> lista_de_clusters = clustering.getListaClusters();
			for (unsigned int i = 0; i < lista_de_clusters.size() ; i++){
				cout<<"CATEGORIA: "<<i<<"\n";
				vector<Punto> puntos_cluster = (*(lista_de_clusters[i])).getPuntos();
				for (unsigned int j = 0; j < puntos_cluster.size(); j++){
					int numeroDoc = puntos_cluster[j]->getDocumento();
					char* nombreDoc = ManejadorArchivos::ObtenerNombreDoc(numeroDoc);//Esta funcion no existe TDV
					cout<<nombreDoc<<"\n";
				}
			}	
		}	
	}		
	
	
	
		
		
	return 0;
}
