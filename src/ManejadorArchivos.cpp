/*
 * ManejadorArchivos.cpp
 */

#include "ManejadorArchivos.h"

using namespace std;

/**********************************************************************/
/**********************************************************************/


ManejadorArchivos::ManejadorArchivos(){}

/**********************************************************************/
/**********************************************************************/

//Destructor del ManejadorArchivos:
//Cierra el archivo unicamente, no lo destruye
ManejadorArchivos::~ManejadorArchivos() {
  if (miarchivo != NULL) miarchivo.close();
}

/**********************************************************************/
/**********************************************************************/


//ojo: usar solo si hay que abrir y cerrar muchos archivos, sino el destructor cierra el archivo.
//se usa en LevantarListaDePuntos.
void ManejadorArchivos::cerrarArchivo(){
	miarchivo.close();
}	

//Abre el archivo pasado por parametro
//en modo LECTURA
void ManejadorArchivos::abrirLectura(const string &nombre){


	//intenta abrir el archivo en modo lectura
	  miarchivo.open(nombre.c_str(), fstream::in); //in = read.

	  if (!miarchivo.is_open())
	          // si no se puede abrir
	          throw ios_base::failure("El archivo "+nombre+" no se abre");

	}

/**********************************************************************/
/**********************************************************************/


//void ManejadorArchivos::abrirEscritura(const std::string& miruta){

//	miarchivo.open(miruta.c_str(), std::fstream::in);
//}

/**********************************************************************/
/**********************************************************************/


// Lo que lee lo guardo en micadena
// Retorna true si pudo leer una linea, o false en caso contrario
bool ManejadorArchivos::leerUnaLinea(string &micadena){

	
	char linea[1024000];

	  // lee del archivo a la linea, hasta haber leido
	  // MAX_LENGTH caracteres(en este caso 100 kbytes
	  miarchivo.getline( (char*)&linea , 1024000);
	  micadena = linea;

	  if (miarchivo.fail() ) {
	    //chequea si se ha producido un error, se devuelve false
	    miarchivo.clear();
	    return false;
	  }
	  return true;

}

/**********************************************************************/
/**********************************************************************/


// Lo que lee lo guardo en micadena
// Retorna true si pudo leer una linea, o false en caso contrario
bool ManejadorArchivos::leerUnaLineaIndice(string &micadena){

	
	char linea[1024000];

	  // lee del archivo a la linea, hasta haber leido
	  // MAX_LENGTH caracteres(en este caso 100 kbytes
	  miarchivo.getline( (char*)&linea , 1024000, '/');
	  micadena = linea;

	  if (miarchivo.fail() ) {
	    //chequea si se ha producido un error, se devuelve false
	    miarchivo.clear();
	    return false;
	  }
	  return true;
}

/**********************************************************************/
/**********************************************************************/



//Posiciona el cursor en una nueva linea debajo de la actual
void ManejadorArchivos::terminarLinea() {
	
  //intenta escribir en el archivo
  miarchivo << endl;

  if (miarchivo.fail())
    //si se produjo un error, arroja una excepcion
    throw ios_base::failure("No se pudo terminar la linea");
}

/**********************************************************************/
/**********************************************************************/


bool ManejadorArchivos::estaAlFinal(){
	
	return miarchivo.eof();
	
}

/**********************************************************************/
/**********************************************************************/


char* ManejadorArchivos::leerArchivo(){
	
    miarchivo.seekg (0, miarchivo.end);
    int largo = miarchivo.tellg();
    miarchivo.seekg (0, miarchivo.beg);

	char * buffer = new char [2*largo];
	
    miarchivo.read (buffer,largo);
    
    miarchivo.close();

	return buffer;
	
}
/**********************************************************************/
/**********************************************************************/


/*Recibe un vector con numeros de docs, lee el archivo del hash secundario
 *Crea y devuelve la lista de puntos correspondiente. */

//Recibe una lista de numeros de docs NO ORDENADA
vector<Punto> ManejadorArchivos::LevantarListaDePuntosTotal(vector<string> vectorArchivos){


	string auxLinea;
	Punto punto;
	vector<Punto> lista_de_puntos;
	this->abrirLectura(DIR_FILE_INDICE_FINAL);//

	int indice = 0;

	char *linea = new char[1024000];
	while ( (this->leerUnaLinea(auxLinea) )){//== true) && (j<numero_doc.size())){

			vector<float> vector_frec;
			strcpy(linea, auxLinea.c_str());
			//auxPalabra va a ir conteniendo cada palabra sacando los tokens
			char* auxPalabra = strtok(linea," ,  ");

			while(auxPalabra != NULL){
				float frec = atof(auxPalabra);
				vector_frec.push_back(frec);
				auxPalabra = strtok(NULL," ,  ");
			}
			punto =  Punto(vector_frec, indice, vectorArchivos[indice]);

			lista_de_puntos.push_back(punto);

			indice++;
			}
	delete []linea;
	this->cerrarArchivo();
	//cout<<"MANEJADOR LISTA DE PUNTOS SIZE: "<<lista_de_puntos.size()<<endl;
	return lista_de_puntos;
}

/**********************************************************************/
/**********************************************************************/


/*Recibe un vector con numeros de docs, lee el archivo del hash secundario 
 *Crea y devuelve la lista de puntos correspondiente. */

//Recibe una lista de numeros de docs NO ORDENADA
vector<Punto> ManejadorArchivos::LevantarListaDePuntos(vector<int> numero_doc, vector<string> vectorArchivos){

	//ordena la lista:
	
	std::sort (numero_doc.begin(), numero_doc.end());
	string auxLinea;
	Punto punto;
	vector<Punto> lista_de_puntos;
	this->abrirLectura(DIR_FILE_INDICE_FINAL);//

	int indice = 0;
	unsigned int j = 0;
	char *linea = new char[1024000];
	//cout<<"size docs postorder: "<<numero_doc.size()<<endl;
	while ( (this->leerUnaLinea(auxLinea) == true) && (j<numero_doc.size())){
		//cout<<"J : "<<j<<endl;
		int doc = numero_doc[j];
		//cout<<"numero doc:  "<<doc<<endl;
		if (indice != doc) { //no es el doc que busco:
			indice++;
			continue;
			//cout<<"INDICES NOT DOC\n";
		}else { //para un doc que busco:
			//cout<<"ELSE\n";
			vector<float> vector_frec;
			strcpy(linea, auxLinea.c_str()); 
			//auxPalabra va a ir conteniendo cada palabra sacando los tokens
			char* auxPalabra = strtok(linea," ,  ");

			while(auxPalabra != NULL){
				//cout<<"WHILE NOT NULL\n";
				//std::string::size_type sz;     // alias of size_t
				float frec = atof(auxPalabra);
				//long float frec = std::stold (auxPalabra,&sz);
				vector_frec.push_back(frec);	
				auxPalabra = strtok(NULL," ,  ");
			}
			punto =  Punto(vector_frec, doc, vectorArchivos[doc]);
			
			lista_de_puntos.push_back(punto);
			
			indice++;
			j++; //pasa al siguiente doc
			//cout<<"J++ : "<<j<<endl;
		}
	}		
	delete []linea;
	this->cerrarArchivo();
	//cout<<"MANEJADOR LISTA DE PUNTOS SIZE: "<<lista_de_puntos.size()<<endl;
	return lista_de_puntos;
}


/**********************************************************************/
/**********************************************************************/


// Lee las claves del archivo file_hash1 y las carga en memoria con frecuencia cero.
map<string, int> ManejadorArchivos::LevantarHashPrincipal(){

	string auxLinea;
	this->abrirLectura(DIR_FILE_HASH_1);
	float frecuencia;
	hash hashPrincipal;
	string clave;
	char* aux;
	char *linea = new char[1024000];
	while ( leerUnaLineaIndice(auxLinea)){		
		strcpy(linea, auxLinea.c_str());
		aux = strtok(linea, ",/ ");
			while (aux != NULL) {			
			clave = aux;
			frecuencia = atof(strtok(NULL, ",/ "));
			//cout<<clave<<",";
			//cout<<endl<<frecuencia<<",";
			aux = strtok(NULL, ",/ ");
			hashPrincipal[clave] = frecuencia;
		}
	}
	delete []linea;
	return hashPrincipal;
}
